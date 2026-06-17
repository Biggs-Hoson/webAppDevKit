

#include "AppNodeTemplate.h"
#include "json/value.h"
#include <optional>

AppNodeTemplate::AppNodeTemplate(const Json::Value& AddressNodeJson)
    : AddressNodeTemplate(std::nullopt)
{
    ExpectedKeys.push_back({
        "defaultRoute", 
        Json::stringValue, 
        true, 
        [this](const Json::Value& value) 
            { ParseDefaultDeployment(value); }
    });

    // May need to remove path

    ParseJson(AddressNodeJson);
};

void AppNodeTemplate::ParseDefaultDeployment(const Json::Value& obj)
{
    defaultDeployment = obj.asString();
};