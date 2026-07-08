#ifndef addressTreeManager
#define addressTreeManager

#include <memory>
#include <vector>

#include "../../ServerInfrastructure/Routing/AddressNode/AddressNode.h"
#include "../../Apps/AppConfig/AppRouteDeployment/AppRouteDeployment.h"

#include "../Manager.h"

class AddressTreeManager  : public Manager
{
    public:
        AddressTreeManager(ServerContextProvider*);

        void DeployAppRoute(AppRouteDeployment&, AppNodeTemplate&);

        AddressNodeChildren* GetAddressTreePtr();

    private:
        // Top level route nodes of the server
    	std::unique_ptr<AddressNodeChildren> AddressTreePtr;
};


#endif