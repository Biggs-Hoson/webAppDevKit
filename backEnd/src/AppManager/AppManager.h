#ifndef appManager
#define appManager

#include <string>
#include <vector>
#include <drogon/drogon.h>
#include "../Routing/RouteNode/RouteNode.h"

class AppManager
{
	public: 
    	AppManager(std::vector<RouteNode>&);
        
    	// Used to deploy an app to the server, structuring its database entities, and loading its config to the appconfig database along with anything else that needs to be done to deploy the app.
        // May also need to recover server state somehow from any lmdb & associated databases
    	void DeployApp(Json::Value&);
        
        // Activates the endpoints for a deployed application
        void ActivateApp();

	private:
    	std::vector<RouteNode>& DomainNodes;
    
    	Json::Value RouteMap;
        
};


#endif