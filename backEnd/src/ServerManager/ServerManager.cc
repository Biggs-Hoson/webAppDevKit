

#include "json/value.h"
#include "ServerManager.h"
#include "../Routing/RouteNode/RouteNode.h"

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
