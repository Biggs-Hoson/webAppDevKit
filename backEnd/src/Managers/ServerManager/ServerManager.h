#ifndef serverManager
#define serverManager

#include <string>
#include <vector>

#include <drogon/drogon.h>

#include "../AppLibraryManager/AppLibraryManager.h"
#include "../RouteTreeManager/RouteTreeManager.h"
#include "../AppDeploymentManager/AppDeploymentManager.h"
#include "../../ServerInfrastructure/Routing/RouteTree/RouteTree.h"

#include "../../ServerInfrastructure/Routing/RouteNode/RouteNode.h"
#include "../../Apps/AppTemplate/RouteNodeTemplate/RouteNodeTemplate.h"
#include "../../ServerInfrastructure/ServerConfig/ServerConfig.h"


// Purpose: a higher level class for managing the server functions the user might interact with, especially for general server functions (Start Server) 
class ServerManager
{
	public: 
    	ServerManager(RouteTree&);

		void DeployAppRouteNode(RouteNodeTemplate&, std::string);

		void StartServer();

	private:

		// Manager Classes
		RouteTreeManager ServerRouteTreeManager;
		AppDeploymentManager ServerAppDeploymentManager;
		AppLibraryManager ServerAppLibraryManager;

		// server Config
		ServerConfig ServerCfg;
};

#endif