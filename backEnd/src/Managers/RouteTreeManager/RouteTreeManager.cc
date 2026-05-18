#include "RouteTreeManager.h";

RouteTreeManager::RouteTreeManager(
    std::vector<RouteNode>& _domains)
	: DomainNodes(_domains) {};

void RouteTreeManager::DeployAppRoute(RouteDeployment& appRouteConfig, AppNodeTemplate& appRouteTemplate)
{
    RouteNode& AppRouteDomain = DomainNodes[appRouteConfig.GetRouteStartId()];

    RouteNode& AppRoute

    AppRouteDomain.DeployAppNodeHere(AppNodeTemplate);
};