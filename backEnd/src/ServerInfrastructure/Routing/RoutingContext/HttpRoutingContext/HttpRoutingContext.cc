#include "./HttpRoutingContext.h"

HttpRoutingContext::HttpRoutingContext(
    const drogon::HttpRequestPtr& req,
    const drogon::HttpResponsePtr& resp,
    ResponseCallback callback
) : RoutingContext(req->getHeader("Host"), req->getPath()),
    RequestPtr(req),
    ResponsePtr(resp),
    CallbackFunction(callback)
{}

bool HttpRoutingContext::CheckMatch(AddressNode* _node)
{
    return _node->GetMatchCritera()->MatchRequest(CurrentSegment);
}

void HttpRoutingContext::HandleNotFound()
{
    if (true) // current node == 0 or current depth == 0
    {
        throw std::make_pair(404, "Domain could not be found");
    }

    // else handle with current error handler node
    
    // else 

    throw std::make_pair(404, "Route could not be found");
}

bool HttpRoutingContext::ResolveWithCurrentNode(AddressNode*)
{
    std::cout << "Resolving" << std::endl;

    ResponsePtr->setBody("Success");

    CallbackFunction(ResponsePtr);

    return true;
}



