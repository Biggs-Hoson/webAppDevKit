#include <fstream>

#include "json/value.h"
#include "ServerManager.h"
#include "../../ServerInfrastructure/Routing/RouteNode/RouteNode.h"
#include "../../ServerInfrastructure/ServerConfig/ServerConfig.h"

ServerManager::ServerManager(std::vector<RouteNode>& _serverRootdomains)
    : ServerRouteTreeManager(_serverRootdomains)
{ 
};



// Sets up server and deploys any saved app configs if possible
void ServerManager::StartServer()
{
    // Deploy all configured apps

    
};


void ServerManager::DeployConfiguredApps()
{
    // Get the currently Configured Apps:


    // For now just load pre-created one

    // Get Appconfig from App Folder
    std::ifstream appJsonFile("./apps/myNotes/myNotes.config.json");

    if (!appJsonFile.is_open()) {
        throw std::make_pair(500, "Could not open myNotes.config.json");
    }

    Json::Value appConfigJson;
    appJsonFile >> appConfigJson;
    appJsonFile.close();

    //Create AppConfig:
    ConfiguredApps.push_back(AppConfig(appConfigJson));

    //Deploy Configured apps
    for(AppConfig& config : ConfiguredApps)
    {
        config.DeployApp(DomainNodes);
    }
};
