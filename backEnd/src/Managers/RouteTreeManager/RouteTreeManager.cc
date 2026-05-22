#include "RouteTreeManager.h";

RouteTreeManager::RouteTreeManager(
    RouteTree& _routeTree)
	: ServerRoutingTree(_routeTree) {};

void RouteTreeManager::DeployAppRoute(RouteDeployment& appRouteConfig, AppNodeTemplate& appRouteTemplate)
{
    //RouteNode& AppRouteDomain = DomainNodes[appRouteConfig.GetRouteStartId()];

    //RouteNode& AppRoute

    //AppRouteDomain.DeployAppNodeHere(AppNodeTemplate);
};