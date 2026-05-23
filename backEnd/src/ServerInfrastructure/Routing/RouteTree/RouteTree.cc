#include "RouteTree.h"

#include <sstream>

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

RouteNode& RouteTree::GetFinalRouteNode(std::string routeString)
{
    std::size_t hostEnd = routeString.find('/');
    int hostEndIndex = routeString.size();


    if (hostEnd!=std::string::npos)
    {
        hostEndIndex = hostEnd;
    }


    while (std::getline(ss, item, '/')) {
        if (!item.empty())
            HostVec.push_back(item);
    }

};

//throw std::pair(503, "Server routing is not functioning currently.");

