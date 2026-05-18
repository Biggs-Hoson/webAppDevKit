#include "AppTemplate.h"
#include "AppNodeTemplate/AppNodeTemplate.h"
#include "../AppComponents/AppVersion/AppVersion.h"
#include "json/value.h"

#include <exception>
#include <string>
#include <vector>

AppTemplate::AppTemplate(Json::Value& _appJson)
{
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
        "routeMap", 
        Json::arrayValue,  // Wrong but kept for testing
        true, 
        [this](const Json::Value& value) 
            { ParseRouteMap(value); }
    });

    ParseJson(_appJson);

    CollectChildErrors(JsonErrors, "");

    PrintErrors();
};

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

void AppTemplate::ParseRouteMap(const Json::Value& _routeMap)
{
    int appRouteCount = 0;

    for (const auto& appRouteJson : _routeMap) {

        if(!appRouteJson.isObject())
        {
            JsonErrors.push_back("routeMap/" + std::to_string(appRouteCount) + ": element is not of type object, expecting AppRouteNode object");
        }
        else 
        {
            AppRouteNodes.push_back(AppNodeTemplate(appRouteJson));
        }
        ++appRouteCount;
    }
};

void AppTemplate::CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath)
{
    for (int i = 0; i < AppRouteNodes.size(); i++) {
        AppRouteNodes[i].CollectErrors(jsonErrors, currentPath + "/routeMap/" + std::to_string(i));
    }
}

AppNodeTemplate& AppTemplate::GetAppNodeById(int appId)
{
    return AppRouteNodes[appId];
}

std::string AppTemplate::GetHash()
{
    return "abxyz";
}

AppVersion& AppTemplate::GetVersion()
{
    return Version;
}