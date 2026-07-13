#ifndef endpointMap
#define endpointMap

#include <memory.h>

#include "drogon/HttpTypes.h"
#include <drogon/drogon.h>
#include <memory>

#include "../EndpointResolver/EndpointResolver.h"

class EndpointMap 
{
    public:
        EndpointResolver* GetEndpoint(drogon::HttpMethod method = drogon::HttpMethod::Get);

    private:
        std::unique_ptr<EndpointResolver> GetMethodResolver;
        std::unique_ptr<EndpointResolver> PostMethodResolver;
        std::unique_ptr<EndpointResolver> HeadMethodResolver;
        std::unique_ptr<EndpointResolver> PutMethodResolver;
        std::unique_ptr<EndpointResolver> DeleteMethodResolver;
        std::unique_ptr<EndpointResolver> OptionsMethodResolver;
        std::unique_ptr<EndpointResolver> PatchMethodResolver;
        std::unique_ptr<EndpointResolver> InvalidMethodResolver;
};

#endif