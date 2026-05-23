#include "ServerManager.h"

ServerManager::ServerManager(RouteTree& _routeTree)
    : ServerRouteTreeManager(_routeTree)
{ 
};

// Sets up server and deploys any saved app configs if possible
void ServerManager::StartServer()
{
    // Deploy all configured apps

    std::vector<AppId> DeployedAppsList = ServerAppDeploymentManager.GetIdsList();

    for (AppId& Id : DeployedAppsList )
    {
        ServerAppDeploymentManager.DeployApp(Id, ServerAppLibraryManager, ServerRouteTreeManager);
    }
};