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
            ResponseCallback,
            AddressNodeChildren*
        );

        void HandleNotFound() override;
    
    protected:
        drogon::HttpRequestPtr RequestPtr;

        drogon::HttpResponsePtr ResponsePtr;

        ResponseCallback& CallbackFunction;

        AddressNodeChildren* ServerAddressTree;

        bool ResolveWithCurrentNode(AddressNode*) override;

        bool TopLevel = false;

};




			

#endif