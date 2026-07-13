#include "./EndpointResolver.h"
#include "drogon/HttpResponse.h"

drogon::HttpResponsePtr EndpointResolver::Resolve(HttpRoutingContext* _context)
{
    drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();

    resp->setBody("Success");
    
    return resp;
};

