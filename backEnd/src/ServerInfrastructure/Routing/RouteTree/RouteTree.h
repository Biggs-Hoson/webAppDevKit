#ifndef routeTree
#define routeTree

#include "../RouteNode/DomainNode/DomainNode.h"
#include "../RequestedRoute/RequestedDomain/RequestedDomain.h"

class RouteTree
{
	public: 
        void RouteRequest(
            const drogon::HttpRequestPtr&,
            drogon::HttpResponsePtr&
        );


    private:
        std::vector<DomainNode> ServerDomainNodes;

        static std::vector<std::string> SplitDomain(const std::string&);

};


#endif