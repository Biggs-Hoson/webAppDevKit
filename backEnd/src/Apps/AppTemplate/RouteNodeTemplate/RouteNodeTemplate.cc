

#include "RouteNodeTemplate.h"
#include "json/value.h"
#include <optional>
#include <string>

RouteNodeTemplate::RouteNodeTemplate(const std::optional<const Json::Value>& RouteNodeJson)
{
    //Register ExpectedKeys
    ExpectedKeys.push_back({"path", 
            Json::stringValue, 
            true, 
            std::nullopt});

    ExpectedKeys.push_back({"subPaths", 
            Json::arrayValue, 
            false, 
            [this](const Json::Value& value) 
            { ParseSubRoutes(value); }
        });

    if(RouteNodeJson.has_value())
    {
        ParseJson(RouteNodeJson.value());
    }
};

void RouteNodeTemplate::ParseSubRoutes(const Json::Value& subRoutesArr)
{
    for(Json::Value subRoute : subRoutesArr)
    {
        SubRoutes.push_back(RouteNodeTemplate(subRoute));
    }
}

void RouteNodeTemplate::CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath)
{
    for (int i = 0; i < SubRoutes.size(); i++) {
        SubRoutes[i].CollectErrors(jsonErrors, currentPath + "/subPaths/" + std::to_string(i));
    }
};