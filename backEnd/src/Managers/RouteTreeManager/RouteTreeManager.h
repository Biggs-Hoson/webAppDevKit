#ifndef routeTreeManager
#define routeTreeManager

#include <vector>

#include "../../ServerInfrastructure/Routing/RouteNode/RouteNode.h"
#include "../../ServerInfrastructure/Routing/RouteTree/RouteTree.h"
#include "../../Apps/AppConfig/RouteDeployment/RouteDeployment.h"

class RouteTreeManager 
{
    public:
        RouteTreeManager();

        void DeployAppRoute(RouteDeployment&, AppNodeTemplate&);

        RouteTree* GetRouteTreePtr();

    private:
        // Top level route nodes of the server
    	RouteTree ServerRoutingTree;
};


#endif