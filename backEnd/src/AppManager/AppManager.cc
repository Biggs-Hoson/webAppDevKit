#include <vector>

#include "AppManager.h"
#include "../Routing/RouteNode/RouteNode.h"


AppManager::AppManager(std::vector<RouteNode>& _domains)
	: DomainNodes(_domains) { };

// For now, just use as a setter for the RouteMap variable
void AppManager::DeployApp(Json::Value& _routeMap) {
	RouteMap = _routeMap;
};

void AppManager::ActivateApp() 
{
	// Deploy RouteMap to DomainNodes
	if (!RouteMap.isArray()) {
    	throw std::make_pair(500, "Server RouteMap is badly formatted.");
    }

    for (Json::ArrayIndex i = 0; i < RouteMap.size(); ++i) {
        Json::Value NodeJson = RouteMap[i];

        DomainNodes.push_back(RouteNode(NodeJson));
    }
};
