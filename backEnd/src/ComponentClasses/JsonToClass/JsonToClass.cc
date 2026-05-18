#include "JsonToClass.h"
#include "json/value.h"
#include <string>

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


void JsonToClass::ParseJson(const Json::Value& _jsonObject)
{
    // Create Mappings in constructor then run this to trigger all functions

    std::vector<std::string> jsonKeys = _jsonObject.getMemberNames();

    // Determine if object is empty and if that's allowed
    if(jsonKeys.size() == 0)
    {
        for (KeyCheck CheckCriteria : ExpectedKeys)
        {
            if (CheckCriteria.KeyRequired)
            {
                JsonErrors.push_back(": Object contains no data");
                return;
            }
        }
    }
    
    // Loop over object's keys, parse values, determine if expected keys are present
    for (std::string key : jsonKeys)
    {
        bool keyIsExpected = false;

        for (KeyCheck CheckCriteria : ExpectedKeys)
        {
            if (key != CheckCriteria.Key)
            {
                continue;
            }

            if (_jsonObject[key].type() != CheckCriteria.ValueType)
            {
                JsonErrors.push_back("/" + key + ": value is not of type " + TypeNames.at(CheckCriteria.ValueType));
            }
            else if (CheckCriteria.ParserFunction.has_value())
            {
                (*CheckCriteria.ParserFunction)(_jsonObject[key]);
            }

            keyIsExpected = true;
            break;
        }
        
        if (!keyIsExpected)
        {
            JsonErrors.push_back(": " + key + " is an unexpected key");
        }
    }

    // Check if any required keys are missing
    for (KeyCheck CheckCriteria : ExpectedKeys)   
    {
        if (CheckCriteria.KeyRequired && !_jsonObject.isMember(CheckCriteria.Key))
        {
            JsonErrors.push_back(": the key '" + CheckCriteria.Key + "' was not found");
        }
    }
};

void JsonToClass::CollectErrors(std::vector<std::string>& _jsonErrors, std::string currentPath)
{
    for (std::string error : JsonErrors)
    {
        _jsonErrors.push_back(currentPath + error);
    }

    CollectChildErrors(_jsonErrors, currentPath);
};

void JsonToClass::PrintErrors()
{
    for (std::string error : JsonErrors)
    {
        std::cout << error << std::endl;
    }
};