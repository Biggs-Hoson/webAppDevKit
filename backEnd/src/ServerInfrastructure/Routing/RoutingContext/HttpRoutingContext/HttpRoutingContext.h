#ifndef httpRoutingContext
#define httpRoutingContext

#include "../RoutingContext.h"
#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"
#include <string>

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

        void HandleErrorResponse(
            int errorCode = 500,
            std::string errorMessage = "");

        std::string GetDefaultErrorMessage(int);

        std::string HtmlErrorPage(const std::string&);
};
			

#endif