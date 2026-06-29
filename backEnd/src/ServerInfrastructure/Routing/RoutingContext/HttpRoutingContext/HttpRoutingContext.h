#ifndef httpRoutingContext
#define httpRoutingContext

#include <string>
#include <vector>

#include "../RoutingContext.h"
#include "../MatchCriteria/MatchCriteria.h"

class HttpRoutingContext : public RoutingContext
{
    public:
        HttpRoutingContext(
            const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
        );
    
    protected:
};




			

#endif