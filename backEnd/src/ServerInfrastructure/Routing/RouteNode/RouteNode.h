#ifndef routeNode
#define routeNode

#include <drogon/drogon.h>
#include <memory>
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

		void DeployAppNodeHere(AppNodeTemplate);

	protected:
        std::unique_ptr<MatchCriteria> MatchCritera;

		bool MatchRequest(
			RequestedRoute*
		);

		std::vector<std::unique_ptr<RouteNode>> SubRoutes; // Automatically routed in if any RequestedRoute.RoutingComplete() == false

		bool RouteRequestInSubroutes(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
		);
		
};

#endif