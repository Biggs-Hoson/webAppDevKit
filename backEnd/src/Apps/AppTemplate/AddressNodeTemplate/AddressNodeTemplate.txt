

#include "AddressNodeTemplate.h"
#include "json/value.h"
#include <optional>
#include <string>

AddressNodeTemplate::AddressNodeTemplate(const std::optional<const Json::Value>& AddressNodeJson)
{
    //Register ExpectedKeys
    ExpectedKeys.push_back({"path", 
            Json::stringValue, 
            true,
        [this](const Json::Value& value) 
            { ParsePath(value); }
        });

    ExpectedKeys.push_back({"subPaths", 
            Json::arrayValue, 
            false, 
            [this](const Json::Value& value) 
            { ParseSubRoutes(value); }
        });

    if(AddressNodeJson.has_value())
    {
        ParseJson(AddressNodeJson.value());
    }
};

void AddressNodeTemplate::ParseSubRoutes(const Json::Value& subRoutesArr)
{
    for(Json::Value subRoute : subRoutesArr)
    {
        SubRoutes.push_back(AddressNodeTemplate(subRoute));
    }
}

void AddressNodeTemplate::ParsePath(const Json::Value& pathStr)
{
    MatchCriteria = pathStr.asString();
}

void AddressNodeTemplate::CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath)
{
    for (int i = 0; i < SubRoutes.size(); i++) {
        SubRoutes[i].CollectErrors(jsonErrors, currentPath + "/subPaths/" + std::to_string(i));
    }
};

std::string AddressNodeTemplate::GetMatchCritera()
{
    return MatchCriteria;
}

std::vector<AddressNodeTemplate>& AddressNodeTemplate::GetSubRoutes()
{
    return SubRoutes;
}