#include "AppRouteDeployment.h"
#include "json/value.h"

AppRouteDeployment::AppRouteDeployment(const Json::Value& AppRouteDeploymentJson)
{
    ExpectedKeys.push_back({
        "appNodeId", 
        Json::intValue,
        true, 
        [this](const Json::Value& value) 
            { ParseAppNodeId(value); }
    });
    
    ExpectedKeys.push_back({
        "appRoute", 
        Json::stringValue,
        true, 
        [this](const Json::Value& value) 
            { ParseAppRoute(value); }
    });

    ParseJson(AppRouteDeploymentJson);
};

void AppRouteDeployment::ParseAppNodeId(const Json::Value& appNodeId)
{
    AppNodeId = appNodeId.asInt();
};

void AppRouteDeployment::ParseAppRoute(const Json::Value& appRoute)
{
    AppRoute = appRoute.asString();
};

void AppRouteDeployment::CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath)
{

};

int AppRouteDeployment::GetAppNodeId()
{
    return AppNodeId;
};

std::string AppRouteDeployment::GetRoute()
{
    return AppRoute;
}