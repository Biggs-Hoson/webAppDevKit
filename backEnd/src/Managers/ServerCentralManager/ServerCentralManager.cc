#include "ServerCentralManager.h"

ServerCentralManager::ServerCentralManager(ServerContextProvider* _provider)
    : Manager(_provider) { };

// Sets up server and deploys any saved app configs if possible
void ServerCentralManager::StartServer()
{
    // Deploy all configured apps

    std::vector<AppId> DeployedAppsList = ServerAppDeploymentManager.GetIdsList();

    for (AppId& Id : DeployedAppsList )
    {
        ServerAppDeploymentManager.DeployApp(Id, ServerAppLibraryManager, ServerAddressTreeManager);
    }
};