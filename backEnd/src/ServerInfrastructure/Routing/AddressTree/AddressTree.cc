#include "AddressTree.h"

#include "../AddressNodeAddress/AddressNodeAddress.h"

void AddressTree::RouteRequest(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp
)
{
    if (RootNodes.size() == 0)
    {
        throw std::pair(503, "Server has no domains set up for routing.");
    }

    std::string host = req->getHeader("Host");

    RequestedDomain domainRequest(host);

	for (AddressNode& RootNodes: RootNodes)
    {
        int responseCode = RootNodes.RouteRequest(req, resp, &domainRequest);

        if (responseCode != 0) {
            return;
        }
    }

    // Top Level 404 error, other 404 errors should be handled in the DomainNode with either a raise or return based on the app's route design.
    throw std::make_pair(404, "Domain could not be found");
};

//Create or add the AddressNodes to fulfill the routeString
AddressNode* AddressTree::GetFinalAddressNode(RouteDeployment& _routeDeployment)
{
    AddressNodeAddress routeAddress(_routeDeployment.GetRoute());

    return RootNodes[_routeDeployment.GetAppNodeId()].GetAddressNode(routeAddress);
};

//throw std::pair(503, "Server routing is not functioning currently.");

