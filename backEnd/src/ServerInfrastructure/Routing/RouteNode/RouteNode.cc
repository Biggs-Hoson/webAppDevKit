#include "RouteNode.h"

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
