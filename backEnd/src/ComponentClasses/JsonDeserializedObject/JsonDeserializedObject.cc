#include "JsonDeserializedObject.h"
#include "json/value.h"
#include <exception>
#include <string>
#include <utility>

const std::map<Json::ValueType, std::string> TypeNames = 
{
    {Json::nullValue, ":null"},
    {Json::intValue, ":int"},
    {Json::uintValue, ":uint"},
    {Json::realValue, ":real"},
    {Json::stringValue, ":str"},
    {Json::booleanValue, ":bool"},
    {Json::arrayValue, ":arr"},
    {Json::objectValue, ":obj"}
};


void JsonDeserializationErrors::AppendError(std::string path, std::string error)
{
    Errors.emplace_back(std::make_pair(path, error));
}

int JsonDeserializedObject::DeserializedJson(
    const Json::Value& jsonToDeserialize, 
    JsonDeserializationErrors* _errorsPtr,
    std::string _currentPath)
{
	CurrentPath = _currentPath;
	ErrorsPtr = _errorsPtr;

    std::vector<std::string> jsonKeys = jsonToDeserialize.getMemberNames();

    //Quick Check for valid object:
	if (jsonKeys.size() == 0 && ParsingRules.size() > 0)
    {
        RecordError("Object contains no data");
        return 0;
    }    

    for (std::string key : jsonKeys)
    {
        Json::ValueType type = jsonToDeserialize[key].type();

        if (type == Json::ValueType::arrayValue)
        {
            int appRouteCount = 0;

            for (const Json::Value& jsonElement : jsonToDeserialize[key]) {

                JsonArrayIndex[key] = appRouteCount;

                type = jsonElement.type();

                if (type == Json::ValueType::arrayValue)
                {
                    RecordError(
                        "multi-dimensional arrays, not supported", 
                        key + "/" + std::to_string(appRouteCount));
                }
                else {
                    ParseKey(
                    jsonElement,
                    type, 
                    key + ":arr", 
                    key + "/" + std::to_string(appRouteCount));
                }
                
                ++appRouteCount;
            }

        }


        ParseKey(jsonToDeserialize[key],type,key);
    }

    // Error Checking

	// Loop over rules, apply parsing logic to see if they are passing or failing

    // If object has any specific type or mode as defined by its present keys,
    // return the appropriate int

    return 0;
};


void JsonDeserializedObject::RecordError(std::string error, std::string key)
{
    if(key != "")
    {
        ErrorsPtr->AppendError(CurrentPath + "/" + key, error);
    }
    else
    {
        ErrorsPtr->AppendError(CurrentPath, error);
    }
};

void JsonDeserializedObject::AddParsingRule(std::string rule, std::string errorMsg)
{
    ParsingRules.insert(std::make_pair(rule, errorMsg));
};


void JsonDeserializedObject::RemoveParsingRule(std::string rule)
{
    std::map<std::string, std::string>::iterator iter = ParsingRules.find(rule) ;
    if( iter != ParsingRules.end() )
        ParsingRules.erase( rule );
    else throw ( "not found" );
};

void JsonDeserializedObject::ParseKey(
    const Json::Value& jsonToDeserialize,
    Json::ValueType& type,
    std::string key,
    std::string location)
{
    if (location == "")
    {
        location = key;
    }

    std::string parserKey = key + TypeNames.at(type);
	
    try
    {
        if (KeyParsers.count(parserKey) > 0)
        {
            KeyParsers[parserKey](jsonToDeserialize);
        }
        else if (KeyParsers.count(key) > 0) // Generic Parser Fallback
        {
            KeyParsers[key](jsonToDeserialize);
        }
        else
        {
            RecordError("No parser found for key.", key);
        }
    }
    catch (std::string err)
    {
        RecordError(err, location);
    }
    catch (char* err)
    {
        RecordError(err, location);
    }
    catch (std::exception ex)
    {
        RecordError(ex.what(), location);
    }
    catch (...)
    {
        RecordError("Something when wrong while parsing this value", location);
    }
};