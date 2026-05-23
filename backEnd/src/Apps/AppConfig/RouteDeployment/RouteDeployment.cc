#include "RouteDeployment.h"
#include "json/value.h"

RouteDeployment::RouteDeployment(const Json::Value& routeDeploymentJson)
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

    ParseJson(routeDeploymentJson);
};

void RouteDeployment::ParseAppNodeId(const Json::Value& appNodeId)
{
    AppNodeId = appNodeId.asInt();
};

void RouteDeployment::ParseAppRoute(const Json::Value& appRoute)
{
    AppRoute = appRoute.asString();
};

void RouteDeployment::CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath)
{

};

int RouteDeployment::GetAppNodeId()
{
    return AppNodeId;
};

std::string RouteDeployment::GetRoute()
{
    return AppRoute;
}