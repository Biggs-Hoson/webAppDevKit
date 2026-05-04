#ifndef appManager
#define appManager

#include <string>
#include <vector>
#include <drogon/drogon.h>
#include "../../Routing/RouteNode/RouteNode.h"
#include "../AppTemplate/AppTemplate.h"
#include "../../ServerManager/ServerManager.h"

class AppManager
{
	public: 
    	AppManager(ServerManager&);
        
		// Register Apps loads the appfiles ready for deployment.
		void RegisterApp(std::string);
        
    	// Used to deploy an app to the server, structuring its database entities, and loading its config to the appconfig database along with anything else that needs to be done to deploy the app.
        // May also need to recover server state somehow from any lmdb & associated databases
    	void DeployApp(std::string);

        // Activates the endpoints for a deployed application
        void ActivateApp();

	private:
		ServerManager ServerManagerObj;

    	Json::Value RouteMap;

		Json::Value ReadAppJson(std::string&);

		std::vector<AppTemplate> RegisteredApps;
};


#endif