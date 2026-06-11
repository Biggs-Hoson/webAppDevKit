#ifndef routeNode
#define routeNode

#include <drogon/drogon.h>
#include <memory>
#include <string>

#include "../../../Apps/AppTemplate/AppNodeTemplate/AppNodeTemplate.h"
#include "../RequestedRoute/RequestedRoute.h"
#include "../RouteNodeAddress/RouteNodeAddress.h"



class RouteNode {
	public:
		RouteNode(RouteNodeTemplate&);

		int RouteRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
		);
        
		virtual int ResolveRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		);
		
		void StructureFromTemplate(RouteNodeTemplate&);

		virtual RouteNode* GetRouteNode(RouteNodeAddress&, bool = false);

		RouteNode* GetRouteNodeInSubRoutes(RouteNodeAddress&, bool = false);

	protected:
        std::unique_ptr<MatchCriteria> MatchCriteraPtr;

		bool MatchRequest(
			RequestedRoute*
		);

		std::vector<std::unique_ptr<RouteNode>> SubRoutes; // Automatically routed in if any RequestedRoute.RoutingComplete() == false

		bool RouteRequestInSubroutes(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
		);

		virtual void CreateSubRoute(RouteNodeTemplate);
		
		virtual RouteNode* AddressFound(RouteNodeAddress&, bool);
};

#endif