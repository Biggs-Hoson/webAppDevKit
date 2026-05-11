#include "RouteDeployment.h"

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
        "routeStartId", 
        Json::intValue,
        true, 
        [this](const Json::Value& value) 
            { ParseRouteStartId(value); }
    });
    
    ExpectedKeys.push_back({
        "subdomainRoute", 
        Json::arrayValue,
        true, 
        [this](const Json::Value& value) 
            { ParseSubdomainRoute(value); }
    });
    
    ExpectedKeys.push_back({
        "pathRoute", 
        Json::arrayValue,
        true, 
        [this](const Json::Value& value) 
            { ParsePathRoute(value); }
    });

    ParseJson(routeDeploymentJson);
};

void RouteDeployment::ParseAppNodeId(const Json::Value& appNodeId)
{
    AppNodeId = appNodeId.asInt();
};

void RouteDeployment::ParseRouteStartId(const Json::Value& routeStartId)
{
    RouteStartId = routeStartId.asInt();
};

void RouteDeployment::ParseSubdomainRoute(const Json::Value& subdomainRoute)
{
    for (const Json::Value& subdomainJson : subdomainRoute)
    {
        SubdomainRoute.push_back(subdomainJson.asString()); 
    }
};

void RouteDeployment::ParsePathRoute(const Json::Value& pathRoute)
{
    for (const Json::Value& pathJson : pathRoute)
    {
        PathRoute.push_back(pathJson.asString()); 
    }
};

void RouteDeployment::CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath)
{

};