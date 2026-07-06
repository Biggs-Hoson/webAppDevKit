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


// Purpose: a higher level class for managing the server functions the user might interact with, especially for general server functions (Start Server) 
class ServerManager
{
	public: 
    	ServerManager();

		void StartServer();

		AddressTreeManager* GetAddressTreeManagerPtr();

	private:

		// Manager Classes
		AddressTreeManager ServerAddressTreeManager;
		AppDeploymentManager ServerAppDeploymentManager;
		AppLibraryManager ServerAppLibraryManager;

		// Server Config
		ServerConfig ServerCfg;
};

#endif