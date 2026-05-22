#include "RouteTree.h"

#include "../../RequestedRoute/RequestedDomain/RequestedDomain.h"

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

//throw std::pair(503, "Server routing is not functioning currently.");