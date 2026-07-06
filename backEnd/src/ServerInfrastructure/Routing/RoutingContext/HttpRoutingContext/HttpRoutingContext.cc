#include "./HttpRoutingContext.h"

HttpRoutingContext::HttpRoutingContext(
    const drogon::HttpRequestPtr& req,
    ResponseCallback callback,
    AddressNodeChildren* initialTree
) : RoutingContext(req->getHeader("Host"), req->getPath(), initialTree),
    RequestPtr(req),
    CallbackFunction(callback),
    ServerAddressTree(initialTree)
{
    ServerAddressTree->RouteRequestInChildren(this);
}

void HttpRoutingContext::HandleNotFound()
{
    // else handle with current error handler node

    if (RoutingInPath()) // May want to give more descriptive location errors later
    {
        if(CurrentSegment == PathSplit.begin())
        {
            throw std::make_pair(404, "First Path Segment could not be found at this domain");
        }

        throw std::make_pair(404, "Path could not be found");
    }
    else {
        if (CurrentSegment == --DomainSplit.end() || ++CurrentSegment == --DomainSplit.end())
        {
            throw std::make_pair(404, "Domain could not be found");
        }

        throw std::make_pair(404, "Subdomain could not be found");
    }
}

bool HttpRoutingContext::ResolveWithCurrentNode(AddressNode*)
{
    drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();

    resp->setBody("Success");

    CallbackFunction(resp);

    return true;
}



