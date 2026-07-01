#include "./HttpRoutingContext.h"

HttpRoutingContext::HttpRoutingContext(
    const drogon::HttpRequestPtr& req,
    const drogon::HttpResponsePtr& resp,
    std::function<void(const drogon::HttpResponsePtr&)>& callback
) : RoutingContext(req->getHeader("Host"), req->getPath()) 
{
    requestPtr = req;

    callbackFunction = callback;
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
    //callbackFunction(resp)

    return true;
}