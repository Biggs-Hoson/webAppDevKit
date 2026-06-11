#include "RouteTree.h"

#include "../RouteNodeAddress/RouteNodeAddress.h"

void RouteTree::RouteRequest(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp
)
{
    if (ServerDomainNodes.size() == 0)
    {
        throw std::pair(503, "Server has no domains set up for routing.");
    }

    std::string host = req->getHeader("Host");

    RequestedDomain domainRequest(host);

	for (RouteNode& DomainNode: ServerDomainNodes)
    {
        int responseCode = DomainNode.RouteRequest(req, resp, &domainRequest);

        if (responseCode != 0) {
            return;
        }
    }

    // Top Level 404 error, other 404 errors should be handled in the DomainNode with either a raise or return based on the app's route design.
    throw std::make_pair(404, "Domain could not be found");
};

//Create or add the routeNodes to fulfill the routeString
RouteNode* RouteTree::GetFinalRouteNode(RouteDeployment& _routeDeployment)
{
    RouteNodeAddress routeAddress(_routeDeployment.GetRoute());

    return ServerDomainNodes[_routeDeployment.GetAppNodeId()].GetRouteNode(routeAddress);
};

//throw std::pair(503, "Server routing is not functioning currently.");

