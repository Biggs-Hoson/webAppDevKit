#ifndef mainFunctions
#define mainFunctions

#include <string>
#include <vector>

#include <drogon/drogon.h>

/*
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
*/

#include "../../ServerInfrastructure/Routing/RouteNode/RouteNode.h"

std::string HtmlErrorPage(const std::string&);

std::vector<std::string> SplitDomain(const std::string&);

void RouteRequest(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp);

void HandleErrorResponse(
    std::shared_ptr<drogon::HttpResponse>,
    drogon::ContentType&,
    int,
    const std::string&);

std::string GetDefaultErrorMessage(int);

void commonHandler(
    const drogon::HttpRequestPtr&,
    std::function<void(const drogon::HttpResponsePtr&)>&&
);

#endif