#ifndef routeTree
#define routeTree

#include "../RouteNode/DomainNode/DomainNode.h"
#include "../RequestedRoute/RequestedDomain/RequestedDomain.h"
#include "../../../Apps/AppConfig/RouteDeployment/RouteDeployment.h"
#include <optional>

class RouteTree
{
	public: 
        void RouteRequest(
            const drogon::HttpRequestPtr&,
            drogon::HttpResponsePtr&
        );

        RouteNode* GetFinalRouteNode(RouteDeployment&);


    private:
        std::vector<DomainNode> ServerDomainNodes;

};


#endif