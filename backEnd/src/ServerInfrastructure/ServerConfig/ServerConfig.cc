#include "ServerConfig.h"

ServerConfig::ServerConfig(std::string _configPath)
{
    GetServerConfig(_configPath);
};

void ServerConfig::GetServerConfig(std::string _configPath)
{
    ExpectedKeys.push_back({
        "rootDomain", 
        Json::arrayValue,
        true, 
        [this](const Json::Value& value) 
            { ParseRootDomains(value); }
    });
    

    // Load Domains from config
    drogon::app().loadConfigFile(_configPath);

    ParseJson(drogon::app().getCustomConfig());
};


void ServerConfig::ParseRootDomains(const Json::Value& rootDomainsConfig)
{
    int i = 0;

    for (const Json::Value& rootDomainJson : rootDomainsConfig)
    {
        if (!rootDomainJson.isString())
        {
            JsonErrors.push_back("rootDomains/" + std::to_string(i) +": domain is not of type string");
        }
        else
        {
            // Perform further parsing to confirm that domain is valid
            RootDomains.push_back(rootDomainJson.asString());
        }

        i++;
    }

    if (!i)
    {
        JsonErrors.push_back("rootDomains: no domains listed");
    }
};

void ServerConfig::CollectChildErrors(std::vector<std::string>& jsonArray, std::string)
{

};