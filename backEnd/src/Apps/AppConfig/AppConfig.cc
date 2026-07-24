#include "AppConfig.h"
#include "AppRouteDeployment/AppRouteDeployment.h"



AppConfig::AppConfig(const Json::Value& configData) {

    RegisterIntField("appId", &AppConfigId);
    
    RegisterStringField("appName", &AppName);
    
    RegisterStringField("appVersion", &CorrespondingAppVersion);
    
    RegisterStringField("appHash", &AppHash);

    RegisterObjectArrayElement("appAppRouteDeployments", &AppRouteDeployments);
    
    DeserializedJson(_appJson, &DeserializationErrors);
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