#include <fstream>

#include "json/value.h"
#include "ServerManager.h"
#include "../../ServerInfrastructure/ServerConfig/ServerConfig.h"

ServerManager::ServerManager(RouteTree& _routeTree)
    : ServerRouteTreeManager(_routeTree)
{ 
};

// Sets up server and deploys any saved app configs if possible
void ServerManager::StartServer()
{
    // Deploy all configured apps

    
};