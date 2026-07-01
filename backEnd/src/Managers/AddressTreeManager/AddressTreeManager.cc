#include "AddressTreeManager.h"

AddressTreeManager::AddressTreeManager()
{
    // Inform AddressTree Manager of hosts

};

void AddressTreeManager::DeployAppRoute(
    AppRouteDeployment& appRouteConfig,
    AppNodeTemplate& appRouteTemplate
)
{
    //Get AppRoute
    //AddressNode* AppAddressNodePtr = ServerRoutingTree.GetFinalAddressNode(appRouteConfig);

    //AppAddressNodePtr->StructureFromTemplate(appRouteTemplate);
};

AddressTree* AddressTreeManager::GetAddressTreePtr()
{
    return &ServerAddressTree;
};


// Server Domains in config are places that the server can deploy to, the one it's listening too.
// Empty means that its only deployment is at 0.0.0.0/ in path only mode

// AddressNode deployments store their complete route, not relative to a routeDomain

// Need to decide how the reserved routes are structured (later)

// Set up PathOnlyMode:

// Need to consider how the server works, because it has an initial setup (path Mode, domains)
// Before the AddressNodes are Deployed.

// Ideally, nothing should be touched after deployment so that the configs still work
// changes should be made via the Web GUI

//Set up domain Roots
//Construct path to approute
//Set up approute