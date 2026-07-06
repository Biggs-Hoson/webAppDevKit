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
            ResponseCallback,
            AddressNodeChildren*
        );

        void HandleNotFound() override;
    
    protected:
        drogon::HttpRequestPtr RequestPtr;

        ResponseCallback& CallbackFunction;

        AddressNodeChildren* ServerAddressTree;

        bool ResolveWithCurrentNode(AddressNode*) override;

        bool TopLevel = false;

};
			

#endif