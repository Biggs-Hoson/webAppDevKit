#include "AppTemplate.h"
#include "json/value.h"

#include <string>
#include <vector>

AppTemplate::AppTemplate(Json::Value& _appJson)
{
    //Register ExpectedKeys
    ExpectedKeys.push_back({
        "appName", 
        Json::stringValue, 
        true, 
        [this](const Json::Value& value) 
            { ParseAppName(value); }
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
