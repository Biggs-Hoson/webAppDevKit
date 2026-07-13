#include "ServerCentralManager.h"

ServerCentralManager::ServerCentralManager()
{
    ServerCentralManagerPtr = this;
};

// Sets up server and deploys any saved app configs if possible
void ServerCentralManager::StartServer()
{
    // Deploy all configured apps

    std::vector<AppId> DeployedAppsList = AppDeploymentManagerPtr->GetIdsList();

    for (AppId& Id : DeployedAppsList )
    {
        AppDeploymentManagerPtr->DeployApp(Id);
    }
};