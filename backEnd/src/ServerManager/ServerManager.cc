#include <fstream>

#include "json/value.h"
#include "ServerManager.h"
#include "../Routing/RouteNode/RouteNode.h"
#include "../Apps/AppConfig/AppConfig.h"
#include "../Apps/AppManager/AppManager.h"

ServerManager::ServerManager(std::vector<RouteNode>& _domains)
	: DomainNodes(_domains) {};

void ServerManager::GetDomainsFromConfig()
{
    Json::Value serverConfig = drogon::app().getCustomConfig();

    if (!serverConfig.isMember("domains"))
    {
    	throw std::make_pair(500, "Server's config does not contain a domain section.");
    }

    Json::Value& serverConfigDomain = serverConfig["domains"];

    if (!serverConfigDomain.isArray()) {
    	throw std::make_pair(500, "Server's accepted domains config is badly formatted.");
    }

    if (serverConfigDomain.size() == 0)
    {
        throw std::make_pair(500, "Server's accepted domains config is empty.");
    }

    for (const auto& domain : serverConfigDomain) {
        if (domain.isString()) {
            ServerDomains.push_back(domain.asString());
        }
        else {
            throw std::make_pair(500, "One of the domains in the accepted domains list is not a string: " + domain.asString());
        }
    }
};

// 
void ServerManager::StartServer()
{
    // Incredibly temporary code here:

    // Create path only domain:
    Json::Value domainRoot;
    domainRoot["domain"] = "*";
    DomainNodes.push_back(RouteNode(domainRoot, DOMAIN));

    //Create AppTemplate
    AppManager ServerAppManager;

    // FOR NOW:: just register the myNotes app manually
    ServerAppManager.RegisterApp("myNotes");

    DeployConfiguredApps();

    //AppTemplate _appTemplate = ServerAppManager.GetApp();

    //DomainNodes[0].DeployAppNodeHere(_appTemplate.GetFirstAppNode());

    // Deploy MyNotes
};


void ServerManager::DeployConfiguredApps()
{
    // Get the currently Configured Apps:

    std::vector<AppConfig> ConfiguredApps;

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
