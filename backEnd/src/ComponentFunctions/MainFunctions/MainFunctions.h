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

#include "../../ServerInfrastructure/Routing/AddressNode/AddressNode.h"

std::string HtmlErrorPage(const std::string&);

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