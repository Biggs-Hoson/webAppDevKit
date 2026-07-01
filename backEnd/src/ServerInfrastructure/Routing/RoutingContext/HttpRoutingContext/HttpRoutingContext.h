#ifndef httpRoutingContext
#define httpRoutingContext

#include <string>
#include <vector>

#include "../RoutingContext.h"
#include "drogon/HttpRequest.h"

class HttpRoutingContext : public RoutingContext
{
    public:
        HttpRoutingContext(
            const drogon::HttpRequestPtr&,
            const drogon::HttpResponsePtr&,
            std::function<void(const drogon::HttpResponsePtr&)>&
        );

        void HandleNotFound() override;
    
    protected:
        drogon::HttpRequestPtr requestPtr;

        std::function<void(const drogon::HttpResponsePtr&)>&& callbackFunction;

        bool CheckMatch(AddressNode*) override;

        bool ResolveWithCurrentNode(AddressNode*) override;

};




			

#endif