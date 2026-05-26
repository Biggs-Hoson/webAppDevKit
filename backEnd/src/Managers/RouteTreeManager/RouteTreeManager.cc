#include "RouteTreeManager.h"

RouteTreeManager::RouteTreeManager() {};

void RouteTreeManager::DeployAppRoute(
    RouteDeployment& appRouteConfig,
    AppNodeTemplate& appRouteTemplate
)
{
    //Get AppRoute
    RouteNode* AppRouteNodePtr = ServerRoutingTree.GetFinalRouteNode(appRouteConfig.GetRoute());

    AppRouteNodePtr->DeployAppNodeHere(appRouteTemplate);
};

RouteTree* RouteTreeManager::GetRouteTreePtr()
{
    return &ServerRoutingTree;
};


// Server Domains in config are places that the server can deploy to, the one it's listening too.
// Empty means that its only deployment is at 0.0.0.0/ in path only mode

// RouteNode deployments store their complete route, not relative to a routeDomain

// Need to decide how the reserved routes are structured (later)

// Set up PathOnlyMode:

// Need to consider how the server works, because it has an initial setup (path Mode, domains)
// Before the routeNodes are Deployed.

// Ideally, nothing should be touched after deployment so that the configs still work
// changes should be made via the Web GUI

//Set up domain Roots
//Construct path to approute
//Set up approute