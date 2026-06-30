#include "AppConfig.h"
#include "AppRouteDeployment/AppRouteDeployment.h"

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
        "appAppRouteDeployments", 
        Json::arrayValue,
        true, 
        [this](const Json::Value& value) 
            { ParseAppAppRouteDeployments(value); }
    });

    ParseJson(configData);  

    CollectChildErrors(JsonErrors, "");
};
        
            
void AppConfig::ParseAppId(const Json::Value& _appId)
{
    AppConfigId.SetId(_appId.asString());
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

void AppConfig::ParseAppAppRouteDeployments(const Json::Value& appAppRouteDeployments)
{
    for(const Json::Value AppRouteDeploymentJson : appAppRouteDeployments)
    {
        AppRouteDeployments.push_back(AppRouteDeployment(AppRouteDeploymentJson));
    }
};


void AppConfig::CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath)
{
    for (int i = 0; i < AppRouteDeployments.size(); i++) {
        AppRouteDeployments[i].CollectErrors(jsonErrors, currentPath + "/appAppRouteDeployments/" + std::to_string(i));
    }
};

//Getters:
AppId AppConfig::GetConfigId()
{
    return AppConfigId;
};

std::string AppConfig::GetAppName()
{
    return AppName;
}

std::string AppConfig::GetAppHash()
{
    return AppHash;
}

std::vector<AppRouteDeployment>& AppConfig::GetAppRouteDeployments()
{
    return AppRouteDeployments;
};