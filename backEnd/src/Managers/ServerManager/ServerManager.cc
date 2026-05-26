#include "ServerManager.h"

ServerManager::ServerManager() { };

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

RouteTreeManager* ServerManager::GetRouteTreeManagerPtr()
{
    return &ServerRouteTreeManager;
}