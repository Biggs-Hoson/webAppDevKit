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

using ResponseCallback = std::function<void(const drogon::HttpResponsePtr&)>;

void HandleErrorResponse(
    const drogon::HttpRequestPtr&,
    ResponseCallback,
    int,
    const std::optional<std::string>);

std::string GetDefaultErrorMessage(int);

void commonHandler(
    const drogon::HttpRequestPtr&,
    std::function<void(const drogon::HttpResponsePtr&)>&&
);

#endif