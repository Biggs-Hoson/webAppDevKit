#ifndef addressNodeChildren
#define addressNodeChildren

#include "../../../Apps/AppConfig/AppRouteDeployment/AppRouteDeployment.h"
#include "../../../Apps/AppTemplate/AppNodeTemplate/AppNodeTemplate.h"

#include <optional>
#include <memory>

class RoutingContext;
class AddressNode;

class AddressNodeChildren
{
	public: 
        void RouteRequestInChildren(RoutingContext*);

        bool Empty();

    protected:
        virtual void CreateSubRoute(AddressNodeTemplate);
    
    private:
        std::vector<std::unique_ptr<AddressNode>> Routes;
};


#endif