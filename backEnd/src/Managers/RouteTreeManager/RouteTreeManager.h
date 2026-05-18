#ifndef routeTreeManager
#define routeTreeManager

#include <vector>

#include "../../ServerInfrastructure/Routing/RouteNode/RouteNode.h"
#include "../../Apps/AppConfig/RouteDeployment/RouteDeployment.h"

class RouteTreeManager 
{
    public:
        RouteTreeManager(std::vector<RouteNode>&);

        void DeployAppRoute(RouteDeployment&, AppNodeTemplate&);

    private:
        // Top level route nodes of the server
    	std::vector<RouteNode>& DomainNodes;
};


#endif