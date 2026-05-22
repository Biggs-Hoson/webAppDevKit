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
    
    protected:
		bool MatchRequest(
			RequestedRoute*
		) override;

		bool RouteRequestInSubroutes(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
		) override;
        

    private:
        std::vector<DomainNode> SubDomainNodes;

        std::vector<PathNode> PathNodes;

        std::unique_ptr<MatchCriteria> MatchCritera;

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