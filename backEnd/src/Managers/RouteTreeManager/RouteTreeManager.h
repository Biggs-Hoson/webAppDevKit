#ifndef routeTreeManager
#define routeTreeManager

#include <vector>

#include "../../ServerInfrastructure/Routing/RouteNode/RouteNode.h"
#include "../../ServerInfrastructure/Routing/RouteTree/RouteTree.h"
#include "../../Apps/AppConfig/RouteDeployment/RouteDeployment.h"

class RouteTreeManager 
{
    public:
        RouteTreeManager(RouteTree&);

        void DeployAppRoute(RouteDeployment&, AppNodeTemplate&);

    private:
        // Top level route nodes of the server
    	RouteTree& ServerRoutingTree;
};


#endif