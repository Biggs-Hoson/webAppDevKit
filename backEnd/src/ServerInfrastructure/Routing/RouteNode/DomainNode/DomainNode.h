#ifndef domainNode
#define domainNode

#include <memory>

#include "../RouteNode.h"
#include "../PathNode/PathNode.h"

#include "../../RequestedRoute/RequestedPath/RequestedPath.h"

class DomainNode : public RouteNode
{
	public: 

		int ResolveRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		) override;

    private:
        std::vector<PathNode> PathNodes;

        int RoutePath(
            const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
        );

		int HitEndpoint(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		);
};


#endif