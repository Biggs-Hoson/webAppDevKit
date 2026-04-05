#ifndef routing
#define routing

#include <drogon/drogon.h>
#include <string>

#include "../MatchClass/MatchClass.h"

enum RouteSection {
  DOMAIN,
  PATH
};

class RouteNode {
	public: 
		// Constructor, accepts the JSON reference to construct the node and the rest of the tree below it
		RouteNode(Json::Value&, RouteSection&, std::string&);

		int RouteRequest(const drogon::HttpRequestPtr&, drogon::HttpResponsePtr&, RouteSection, std::string&);
        
		int ResolveRequest(const drogon::HttpRequestPtr&, drogon::HttpResponsePtr&);

	private:
    	// Affects the matching function and
    	RouteSection NodeRouteSection;
    	
    	std::unique_ptr<MatchClass> RouteMatchObj;
        
        int RouteRemainingRequest(const drogon::HttpRequestPtr&, drogon::HttpResponsePtr&, RouteSection, std::string&);

		std::string GetRemainingRoute(std::string, int);

		void SetSubRoutes(Json::Value&, std::string&);

        std::vector<RouteNode> SubRoutes;

		void ThrowFormatError(int = 500, std::string = "Server RouteMap is badly formatted.");
};

#endif