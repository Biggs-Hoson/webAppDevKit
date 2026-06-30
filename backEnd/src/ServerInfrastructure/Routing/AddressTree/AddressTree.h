#ifndef addressTree
#define addressTree

#include "../RoutingContext/RoutingContext.h"
#include "../../../Apps/AppConfig/AppRouteDeployment/AppRouteDeployment.h"

#include <optional>
#include <memory>

class AddressTree
{
	public: 
        void RouteRequestInTree(RoutingContext*);

        bool Empty();

    private:
        std::vector<std::unique_ptr<AddressNode>> Routes;
};


#endif