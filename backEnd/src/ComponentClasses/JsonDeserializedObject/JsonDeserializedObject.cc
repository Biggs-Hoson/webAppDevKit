#include "JsonDeserializedObject.h"
#include "json/value.h"
#include <exception>
#include <string>
#include <utility>

const std::map<Json::ValueType, std::string> TypeNames = 
{
    {Json::nullValue, "null"},
    {Json::intValue, "int"},
    {Json::uintValue, "unsigned int"},
    {Json::realValue, "real"},
    {Json::stringValue, "string"},
    {Json::booleanValue, "boolean"},
    {Json::arrayValue, "array"},
    {Json::objectValue, "object"},
};

void JsonDeserializationErrors::AppendError(std::string path, std::string error)
{
    Errors.push_back(std::make_pair(path, error));
}

void JsonDeserializedObject::DeserializedJson(
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
        return;
    }    

    for (std::string key : jsonKeys)
    {
    	std::string parserKey = key + GetJsonTypeName(jsonToDeserialize[key].type());
	
        try
        {
            if (KeyParsers.count(parserKey) > 0)
            {
                KeyParsers[parserKey](jsonToDeserialize[key]);
            }
            else if (KeyParsers.count(key) > 0) // Generic Parser Fallback
            {
                KeyParsers[key](jsonToDeserialize[key]);
            }
            else
            {
                RecordError("No parser found for key.", key);
            }
        }
        catch (std::string err)
        {
            RecordError(err, key);
        }
        catch (char* err)
        {
            RecordError(err, key);
        }
        catch (std::exception ex)
        {
            RecordError(ex.what(), key);
        }
        catch (...)
        {
            RecordError("Something when wrong while parsing this value", key);
        }
    }

    // Error Checking

	// Loop over rules, apply parsing logic to see if they are passing or failing

};

std::string JsonDeserializedObject::GetJsonTypeName(Json::ValueType type)
{
    switch(type)
    {
        case Json::ValueType::nullValue:
            return ":null";
        case Json::ValueType::intValue:
            return ":int";
        case Json::ValueType::uintValue:
            return ":uint";
        case Json::ValueType::realValue:
            return ":real";
        case Json::ValueType::stringValue:
            return ":str";
        case Json::ValueType::booleanValue:
            return ":bool";
        case Json::ValueType::arrayValue:
            return ":arr";
        case Json::ValueType::objectValue:
            return ":obj";
    }

    return ":unknown";
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