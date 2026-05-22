#ifndef routeNode
#define routeNode

#include <drogon/drogon.h>
#include <string>

#include "../../../Apps/AppTemplate/AppNodeTemplate/AppNodeTemplate.h"
#include "../RequestedRoute/RequestedRoute.h"


class RouteNode {
	public: 
		int RouteRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
		);
        
		virtual int ResolveRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		) = 0;

	protected:
		virtual bool MatchRequest(
			RequestedRoute*
		) = 0;

		virtual bool RouteRequestInSubroutes(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
		) = 0;
};

#endif


/*

class RouteNode {
	public: 
		// Constructor, accepts the JSON reference to construct the node and the rest of the tree below it
		//RouteNode(Json::Value&, RouteSection, std::string = "");

		//RouteNode(RouteNodeTemplate, RouteSection, std::string = "");

		int RouteRequest(
			const drogon::HttpRequestPtr& req,
			drogon::HttpResponsePtr& resp,
			RouteSection currentRouteSection, 
			std::vector<std::string>::iterator& nextSection,
			std::vector<std::string>::iterator& finalSection
		);
        
		int ResolveRequest(const drogon::HttpRequestPtr&, drogon::HttpResponsePtr&);

		//void DeployAppNodeHere(AppNodeTemplate);

		//RouteNode& ConstructSubdomains(std::vector<std::string>);

		//RouteNode& ConstructSubPath(std::vector<std::string>);

	private:
    	
    	std::unique_ptr<MatchClass> RouteMatchObj;

        std::vector<RouteNode> SubRoutes;
        
        int RouteRequestInSubroutes(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&,
			RouteSection,
			std::vector<std::string>::iterator&,
			std::vector<std::string>::iterator&
		);

		std::string GetRemainingRoute(std::string, int);

		void SetSubRoutes(Json::Value&, std::string&);

		void ThrowFormatError(int = 500, std::string = "Server RouteMap is badly formatted.");

		std::vector<std::string> SplitOnChar(const std::string& s, const char c);

		bool HasSubdomain(std::string);

		bool HasSubPath(std::string);
};

*/