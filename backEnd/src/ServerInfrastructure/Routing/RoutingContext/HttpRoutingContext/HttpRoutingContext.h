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
            const drogon::HttpRequestPtr& req,
            const drogon::HttpResponsePtr& resp,
            std::function<void(const drogon::HttpResponsePtr&)>& callback
        );
    
    protected:
        drogon::HttpRequestPtr requestPtr;

        std::function<void(const drogon::HttpResponsePtr&)>&& callbackFunction;

        bool CheckMatch(AddressNode*);

        bool ResolveWithCurrentNode(AddressNode*);


};




			

#endif