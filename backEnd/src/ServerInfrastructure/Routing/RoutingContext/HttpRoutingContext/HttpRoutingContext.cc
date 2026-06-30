#include "./HttpRoutingContext.h"

HttpRoutingContext::HttpRoutingContext(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback
) : RoutingContext(req->getHeader("Host"), req->getPath())
{
    requestPtr = req;

    callbackFunction = callback;
}