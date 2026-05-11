#ifndef serverManager
#define serverManager

#include <string>
#include <vector>
#include <drogon/drogon.h>
#include "../Routing/RouteNode/RouteNode.h"
#include "../Apps/AppTemplate/RouteNodeTemplate/RouteNodeTemplate.h"

class ServerManager
{
	public: 
    	ServerManager(std::vector<RouteNode>&);

		void GetDomainsFromConfig();

		void DeployAppRouteNode(RouteNodeTemplate&, std::string);

		void StartServer();

	private:
        // Top level route nodes of the server
    	std::vector<RouteNode>& DomainNodes;

        // Index of the primary domain on the server
        int primaryDomain;

        // A vector of the domains that have been registered to the server.
		std::vector<std::string> ServerDomains;

		void DeployConfiguredApps();
};

#endif