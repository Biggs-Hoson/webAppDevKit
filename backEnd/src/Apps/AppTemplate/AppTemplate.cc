#include "AppTemplate.h"
#include "AppNodeTemplate/AppNodeTemplate.h"
#include "../AppComponents/AppVersion/AppVersion.h"
#include "DatabaseObjectsTemplate/DatabaseObjectsTemplate.h"
#include "json/value.h"

#include <string>
#include <vector>


AppTemplate::AppTemplate(Json::Value& _appJson)
{
    /*
    Version = AppVersion("0");

    //Register ExpectedKeys
    ExpectedKeys.push_back({
        "appName", 
        Json::stringValue, 
        true, 
        [this](const Json::Value& value) 
            { ParseAppName(value); }
    });

    ExpectedKeys.push_back({
        "appVersion", 
        Json::stringValue,  // Wrong but kept for testing
        true, 
        [this](const Json::Value& value) 
            { ParseAppVersion(value); }
    });

    ExpectedKeys.push_back({
        "databaseObjects", 
        Json::arrayValue,  // Wrong but kept for testing
        false, 
        [this](const Json::Value& value) 
            { ParseDatabaseObjects(value); }
    });

    ExpectedKeys.push_back({
        "routeMap", 
        Json::arrayValue,  // Wrong but kept for testing
        true, 
        [this](const Json::Value& value) 
            { ParseRouteMap(value); }
    });
    */
    DeserializedJson(_appJson, &DeserializationErrors);
};


/*
void AppTemplate::ParseAppName(const Json::Value& _appName)
{
    AppName = _appName.asString();

    // Check if AppName is properly formatted
};

void AppTemplate::ParseAppVersion(const Json::Value& _appVersion)
{
    try 
    {
        Version = _appVersion.asString();
    } 
    catch (std::exception e) 
    {
        JsonErrors.push_back("appVersion/: Could not parse version string, should be string of '.' separated numbers");
    }
    
};

void AppTemplate::ParseDatabaseObjects(const Json::Value& _databaseObjects)
{
    dboTemplate = std::make_shared<DatabaseObjectsTemplate>(_databaseObjects);
}

void AppTemplate::ParseRouteMap(const Json::Value& _routeMap)
{
    int appRouteCount = 0;

    for (const auto& appRouteJson : _routeMap) {

        if(!appRouteJson.isObject())
        {
            JsonErrors.push_back("routeMap/" + std::to_string(appRouteCount) + ": element is not of type object, expecting AppAddressNode object");
        }
        else 
        {
            AppAddressNodes.push_back(AppNodeTemplate(appRouteJson));
        }
        ++appRouteCount;
    }
};

void AppTemplate::CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath)
{
    dboTemplate->CollectErrors(jsonErrors, currentPath + "/databaseObjects");

    for (int i = 0; i < AppAddressNodes.size(); i++) {
        AppAddressNodes[i].CollectErrors(jsonErrors, currentPath + "/routeMap/" + std::to_string(i));
    }
}

*/

AppNodeTemplate& AppTemplate::GetAppNodeById(int appId)
{
    return AppAddressNodes[appId];
}

std::string AppTemplate::GetHash()
{
    return "abxyz";
}

std::string AppTemplate::GetName()
{
    return AppName;
}

AppVersion& AppTemplate::GetVersion()
{
    return Version;
}

