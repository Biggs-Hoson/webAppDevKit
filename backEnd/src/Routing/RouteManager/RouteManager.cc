#ifndef routeManager
#define routeManager

#include <vector>

#include "../RouteNode/RouteNode.h"

class RouteManager
{
	public: 
    	RouteManager(std::vector<RouteNode>&);
        
    	// Used to deploy an app to the server, structuring its database entities, and loading its config to the appconfig database along with anything else that needs to be done to deploy the app.
        // May also need to recover server state somehow from any lmdb & associated databases
    	void DeployApp(std::string);
        
        // Activates the endpoints for a deployed application
        void ActivateApp();

		void GetDomainsFromConfig();

	private:
    	std::vector<RouteNode>& DomainNodes;
    
    	Json::Value RouteMap;

		Json::Value ReadAppJson(std::string&);

		std::vector<std::string> ServerDomains;
};


#endif