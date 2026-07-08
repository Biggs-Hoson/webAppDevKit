#ifndef serverManager
#define serverManager

#include <string>
#include <vector>

#include <drogon/drogon.h>

#include "../AppLibraryManager/AppLibraryManager.h"
#include "../AddressTreeManager/AddressTreeManager.h"
#include "../AppDeploymentManager/AppDeploymentManager.h"

#include "../../ServerInfrastructure/Routing/AddressNode/AddressNode.h"
#include "../../Apps/AppTemplate/AddressNodeTemplate/AddressNodeTemplate.h"
#include "../../ServerInfrastructure/ServerConfig/ServerConfig.h"

#include "../Manager.h"


// Purpose: a higher level class for managing the server functions the user might interact with, especially for general server functions (Start Server) 
class ServerCentralManager : public Manager
{
	public: 
    	ServerCentralManager(ServerContextProvider*);

		void StartServer();

	private:
		// Server Config
		ServerConfig ServerCfg;
};

#endif