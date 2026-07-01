#ifndef addressTreeManager
#define addressTreeManager

#include <vector>

#include "../../ServerInfrastructure/Routing/AddressNode/AddressNode.h"
#include "../../ServerInfrastructure/Routing/AddressNodeChildren/AddressTree/AddressTree.h"
#include "../../Apps/AppConfig/AppRouteDeployment/AppRouteDeployment.h"

class AddressTreeManager 
{
    public:
        AddressTreeManager();

        void DeployAppRoute(AppRouteDeployment&, AppNodeTemplate&);

        AddressTree* GetAddressTreePtr();

    private:
        // Top level route nodes of the server
    	AddressTree ServerAddressTree;
};


#endif