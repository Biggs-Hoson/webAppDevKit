#ifndef endpointResolver
#define endpointResolver

#include "drogon/HttpResponse.h"
#include <drogon/drogon.h>

class HttpRoutingContext;

class EndpointResolver
{
    public:
        drogon::HttpResponsePtr Resolve(HttpRoutingContext* context);

    private:
};

#endif