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

        bool HandleErrorResponse();

        bool HandleErrorResponse(int);

        bool HandleErrorResponse(int, std::string);

        std::string GetDefaultErrorMessage();

        std::string HtmlErrorPage(const std::string&);

        void UpdateRoutingContext(AddressNode*) override;

    private:
        EndpointResolver* ErrorResolverPtr;

        int HttpCode = 500;

        std::string HttpResponseMessage = "";
};
			

#endif