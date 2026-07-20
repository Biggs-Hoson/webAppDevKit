#include "./DatabaseObjectsTemplate.h"
#include "TableTemplate/TableTemplate.h"
#include "json/value.h"

DatabaseObjectsTemplate::DatabaseObjectsTemplate(const Json::Value& dboJson)
{
    //Register ExpectedKeys
    ExpectedKeys.push_back({
        "relationalData", 
        Json::arrayValue, 
        false, 
        [this](const Json::Value& value) 
            { ParseRelationalDataTables(value); }
    });

    ParseJson(dboJson);
}

void DatabaseObjectsTemplate::ParseRelationalDataTables(const Json::Value& relationalDataJson)
{
    int tablesCount = 0;

    for (const auto& tableJson : relationalDataJson) {

        if(!tableJson.isObject())
        {
            JsonErrors.push_back("relationalData/" + std::to_string(tablesCount) + ": element is not of type object, expecting a Table object");
        }
        else 
        {
            Tables.push_back(TableTemplate(tableJson));
        }
        ++tablesCount;
    }
};

void DatabaseObjectsTemplate::CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath)
{
    for (int i = 0; i < Tables.size(); i++) {
        Tables[i].CollectErrors(jsonErrors, currentPath + "/relationalData/" + std::to_string(i));
    }
}