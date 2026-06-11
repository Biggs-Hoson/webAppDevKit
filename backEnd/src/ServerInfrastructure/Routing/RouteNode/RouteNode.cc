#include "RouteNode.h"
#include <memory>

int RouteNode::RouteRequest(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp, 
    RequestedRoute* route
)
{
    // Match Request

    if (!MatchRequest(route)){
    	// Match Unsuccessful, return 0 to attempt next RouteNode
        return 0;
    }

    if (route->RoutingComplete())
    {
        return ResolveRequest(req, resp);
    }

    return RouteRequestInSubroutes(req, resp, route);
}

void RouteNode::DeployAppNodeHere(AppNodeTemplate nodeTemplate)
{

};

bool RouteNode::MatchRequest(
    RequestedRoute* _route
)
{
    return _route->MatchRequest(MatchCritera.get());
};

bool RouteNode::RouteRequestInSubroutes(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp,
    RequestedRoute* _route
)
{
    for (std::unique_ptr<RouteNode>& subRoutePtr : SubRoutes){
		int responseCode = subRoutePtr->RouteRequest(req, resp, _route);
		if (responseCode != 0) {
			return responseCode;
		}
	}

    return 404;
};