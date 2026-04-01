#ifndef routing
#define routing

#include <drogon/drogon.h>

#include "../MatchClass/MatchClass.h"

enum RouteSection {
  DOMAIN,
  PATH
};

class RouteNode {
	public: 
		// Constructor, accepts the JSON reference to construct the node and the rest of the tree below it
		RouteNode(Json::Value&);

		int RouteRequest(const drogon::HttpRequestPtr&, drogon::HttpResponsePtr&, RouteSection, std::string&);
        
		int ResolveRequest(const drogon::HttpRequestPtr&, drogon::HttpResponsePtr&);

	private:
    	// Affects the matching function and
    	RouteSection NodeRouteSection;
    	
    	std::unique_ptr<MatchClass> RouteMatchObj;
        
        int RouteRemainingRequest(const drogon::HttpRequestPtr&, drogon::HttpResponsePtr&, RouteSection, std::string&);

		std::string GetRemainingRoute(std::string, int);

        std::vector<RouteNode> SubRoutes;
};

#endif