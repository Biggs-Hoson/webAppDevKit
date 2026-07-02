#ifndef httpRoutingContext
#define httpRoutingContext

#include "../RoutingContext.h"
#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"

class HttpRoutingContext : public RoutingContext
{
    public:
        using ResponseCallback = std::function<void(const drogon::HttpResponsePtr&)>;

        HttpRoutingContext(
            const drogon::HttpRequestPtr&,
            const drogon::HttpResponsePtr&,
            std::function<void(const drogon::HttpResponsePtr&)>
        );

        void HandleNotFound() override;
    
    protected:
        drogon::HttpRequestPtr RequestPtr;

        drogon::HttpResponsePtr ResponsePtr;

        ResponseCallback& CallbackFunction;

        bool CheckMatch(AddressNode*) override;

        bool ResolveWithCurrentNode(AddressNode*) override;

};




			

#endif