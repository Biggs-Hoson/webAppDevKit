#include "./EndpointMap.h"
#include "drogon/HttpTypes.h"

EndpointResolver* EndpointMap::GetEndpoint(drogon::HttpMethod method)
{
    switch (method) {
        case drogon::HttpMethod::Get:
            return GetMethodResolver.get();
            break;
        case drogon::HttpMethod::Post:
            return PostMethodResolver.get();
            break;
        case drogon::HttpMethod::Head:
            return HeadMethodResolver.get();
            break;
        case drogon::HttpMethod::Put:
            return PutMethodResolver.get();
            break;
        case drogon::HttpMethod::Delete:
            return DeleteMethodResolver.get();
            break;
        case drogon::HttpMethod::Options:
            return OptionsMethodResolver.get();
            break;
        case drogon::HttpMethod::Patch:
            return PatchMethodResolver.get();
            break;
        case drogon::HttpMethod::Invalid:
            return InvalidMethodResolver.get();
            break;
    }

    return nullptr;
}