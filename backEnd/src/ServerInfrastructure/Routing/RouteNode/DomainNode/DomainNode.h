#ifndef domainNode
#define domainNode

#include <memory>

#include "../RouteNode.h"

#include "../../RequestedRoute/RequestedPath/RequestedPath.h"

class DomainNode : public RouteNode
{
	public: 
		int ResolveRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		) override;

		void CreateSubRoute(
			RouteNodeTemplate _subNodeTemplate
		) override;


    private:
        std::vector<RouteNode> PathNodes;

        int RoutePath(
            const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
        );

		int HitEndpoint(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		);

		RouteNode* AddressFound(RouteNodeAddress&, bool) override;
};


#endif