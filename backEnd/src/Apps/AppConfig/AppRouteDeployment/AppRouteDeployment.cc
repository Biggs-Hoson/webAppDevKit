#include "AppRouteDeployment.h"
#include "json/value.h"

/*

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

*/

int AppRouteDeployment::GetAppNodeId()
{
    return AppNodeId;
};

std::string AppRouteDeployment::GetRoute()
{
    return AppRoute;
}

std::string AppRouteDeployment::GetDomain()
{
    size_t pos = AppRoute.find('/');

    if (pos == std::string::npos)
    {
        // No slash found, check if entirely domain by looking for a '.' character, else return empty string

        if (AppRoute.find('.') == std::string::npos)
        {
            return "";
        }
        
        return AppRoute;
    }

    return AppRoute.substr(0, pos);
}

std::string AppRouteDeployment::GetPath()
{
    size_t pos = AppRoute.find('/');

    if (pos == std::string::npos)
    {
        // No slash found, check if entirely domain by looking for a '.' character, else return AppRoute as the entire path

        if (AppRoute.find('.') == std::string::npos)
        {
            return AppRoute;
        }
        
        return "";
    }

    return AppRoute.substr(pos + 1);
}