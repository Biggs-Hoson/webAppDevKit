#ifndef AddressTreeManager
#define AddressTreeManager

#include <vector>

#include "../../ServerInfrastructure/Routing/AddressNode/AddressNode.h"
#include "../../ServerInfrastructure/Routing/AddressTree/AddressTree.h"
#include "../../Apps/AppConfig/RouteDeployment/RouteDeployment.h"

class AddressTreeManager 
{
    public:
        AddressTreeManager();

        void DeployAppRoute(RouteDeployment&, AppNodeTemplate&);

        AddressTree* GetAddressTreePtr();

    private:
        // Top level route nodes of the server
    	AddressTree ServerRoutingTree;
};


#endif