#include <vector>
#include <fstream>

#include "AppManager.h"
#include "../Routing/RouteNode/RouteNode.h"


AppManager::AppManager(std::vector<RouteNode>& _domains)
	: DomainNodes(_domains) {};

void AppManager::DeployApp(std::string appName) {

    Json::Value AppJson = ReadAppJson(appName);

    // Deploy RouteMap

    // for testing Force the deployment of the RouteMap to the default address

    if (!AppJson.isMember("routeMap"))
    {
        throw std::make_pair(500, appName + ".json does not contain a routeMap key.");
    }

    Json::Value& RouteMap = AppJson["routeMap"];
    
    if (!RouteMap.isArray()) {
    	throw std::make_pair(500, appName + " routeMap is not an array");
    }
    
    // Deploy each routeTree
    for (Json::ArrayIndex i = 0; i < RouteMap.size(); ++i) {
        Json::Value& RootNodeJson = RouteMap[i];

        // Determine if this specific routeNode can be deployed from a path or if it must be deployed at the domain level.

        bool domainDeployment = false;

        if (RootNodeJson.isMember("subRoutes"))
        {
            Json::Value& nodeSubRoutes = RootNodeJson["subRoutes"];

            if (!nodeSubRoutes.isArray()) {
                throw std::make_pair(500, appName + " routeMap is badly formatted");
            }
            
            for (Json::ArrayIndex i = 0; i < nodeSubRoutes.size(); ++i) {

                if (nodeSubRoutes[i].isMember("domain"))
                {
                    domainDeployment = true;
                    break;
                }
            }
        }

        // Temp:
        bool defaultDeployment = true;

        std::string matchCriteria;

        if (defaultDeployment)
        {
            if (!RootNodeJson.isMember("defaultRoute"))
            {
                throw std::make_pair(500, "A root node in the " + appName + ".json routeMap does not have a defaultRoute property.");
            }

            if (!RootNodeJson["defaultRoute"].isString()) {
                throw std::make_pair(500, "DefaultRoute is not a string.");
            }

            matchCriteria = RootNodeJson["defaultRoute"].asString();

            matchCriteria.replace(matchCriteria.find("*"), 1, "*");

            std::cout << matchCriteria;
        }
        else
        {
        
        }

        RouteSection sec = DOMAIN;

        // Need to plan the collective routeMap system 
        DomainNodes.push_back(RouteNode(RootNodeJson, sec, ServerDomains[0]));
    }
};

void AppManager::GetDomainsFromConfig()
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

    for (const auto& domain : serverConfigDomain) {
        if (domain.isString()) {
            ServerDomains.push_back(domain.asString());
        }
        else {
            throw std::make_pair(500, "Server's accepted domains config is badly formatted.");
        }
    }
    
    if (ServerDomains.size() == 0)
    {
        throw std::make_pair(500, "Server's accepted domains config is empty.");
    }
};

Json::Value AppManager::ReadAppJson(std::string& appName)
{
    std::ifstream appJsonFile("./apps/" + appName + "/" + appName +".json");

    if (!appJsonFile.is_open()) {
        throw std::make_pair(500, "Could not open "+ appName + ".json");
    }

    Json::Value appJson;
    appJsonFile >> appJson;

    appJsonFile.close();

    return appJson;
}

void AppManager::ActivateApp() 
{
    
};
