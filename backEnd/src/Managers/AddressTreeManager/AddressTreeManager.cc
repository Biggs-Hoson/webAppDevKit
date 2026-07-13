#include "AddressTreeManager.h"

#include "../../ServerInfrastructure/Routing/RoutingContext/RouteConstructorContext/RouteConstructorContext.h"
#include <memory>
#include <ostream>

AddressTreeManager::AddressTreeManager()
{
    AddressTreeManagerPtr = this;

    // Inform AddressTree Manager of hosts

    AddressTreePtr = std::make_unique<AddressNodeChildren>();

};

void AddressTreeManager::DeployAppRoute(
    AppRouteDeployment& appRouteConfig,
    AppNodeTemplate& appRouteTemplate
)
{
    try 
    {
        //Get AppRoute
        RouteConstructorContext RouteConstructor(appRouteConfig, GetAddressTreePtr());

        AddressNode* AppAddressNodePtr = RouteConstructor.GetFinalAddresesNodePtr();

        if(AppAddressNodePtr == nullptr)
        {
            throw "Route could not be constructed";
        }
        if (!AppAddressNodePtr->Empty())
        {
            throw "Cannot convert node to AppRoute as it has children";
        }

        AppAddressNodePtr->StructureFromTemplate(appRouteTemplate);
    } 
    catch (...) {
        std::cout << "Invalid Route Deployment Config" << std::endl;
    }
};

AddressNodeChildren* AddressTreeManager::GetAddressTreePtr()
{
    return AddressTreePtr.get();
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