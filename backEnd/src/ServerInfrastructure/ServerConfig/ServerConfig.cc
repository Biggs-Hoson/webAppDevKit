#include "./ServerConfig.h"

ServerConfig::ServerConfig(std::string _configPath)
{   
    GetServerConfig(_configPath);
};

void ServerConfig::GetServerConfig(std::string _configPath)
{
    // Load Domains from config
    drogon::app().loadConfigFile(_configPath);

    Json::Value configJson = drogon::app().getCustomConfig();

    //DeserializedJson(configJson);
};