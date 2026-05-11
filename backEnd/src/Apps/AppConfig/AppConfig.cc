#include "AppConfig.h"
#include "RouteDeployment/RouteDeployment.h"

AppConfig::AppConfig(const Json::Value& configData) {

    //Register ExpectedKeys
    ExpectedKeys.push_back({
        "appId", 
        Json::intValue, 
        true, 
        [this](const Json::Value& value) 
            { ParseAppId(value); }
    });

    ExpectedKeys.push_back({
        "appName", 
        Json::stringValue,
        true, 
        [this](const Json::Value& value) 
            { ParseAppName(value); }
    });

    ExpectedKeys.push_back({
        "appVersion", 
        Json::stringValue,
        true, 
        [this](const Json::Value& value) 
            { ParseAppVersion(value); }
    });

    ExpectedKeys.push_back({
        "appHash", 
        Json::stringValue,
        true, 
        [this](const Json::Value& value) 
            { ParseAppHash(value); }
    });

    ExpectedKeys.push_back({
        "appRouteDeployments", 
        Json::arrayValue,
        true, 
        [this](const Json::Value& value) 
            { ParseAppRouteDeployments(value); }
    });

    ParseJson(configData);  

    CollectChildErrors(JsonErrors, "");
};
        
            
void AppConfig::ParseAppId(const Json::Value& appId)
{
    AppId = appId.asInt();
};

void AppConfig::ParseAppName(const Json::Value& appName)
{
    AppName = appName.asString();
};

void AppConfig::ParseAppVersion(const Json::Value& _appVersion)
{
    try 
    {
        CorrespondingAppVersion = AppVersion(_appVersion.asString());
    } 
    catch (std::exception e) 
    {
        JsonErrors.push_back("appVersion/: Could not parse version string, should be string of '.' separated numbers");
    }
};

void AppConfig::ParseAppHash(const Json::Value& appHash)
{
    AppHash = appHash.asString();
};

void AppConfig::ParseAppRouteDeployments(const Json::Value& appRouteDeployments)
{
    for(const Json::Value routeDeploymentJson : appRouteDeployments)
    {
        RouteDeployments.push_back(RouteDeployment(routeDeploymentJson));
    }
};


void AppConfig::CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath)
{
    for (int i = 0; i < RouteDeployments.size(); i++) {
        RouteDeployments[i].CollectErrors(jsonErrors, currentPath + "/appRouteDeployments/" + std::to_string(i));
    }
};

void AppConfig::GetAppTemplate(AppManager& _appManger)
{
    AppTemplate& AppTemplate = _appManger.FindApp(AppName, &CorrespondingAppVersion);

    if (AppHash != AppTemplate.GetHash())
    {
        throw("App Hash doesn't hash.");
    }
}


void AppConfig::DeployApp(std::vector<RouteNode>& domainRoot)
{
    //FindAppTemplate
};