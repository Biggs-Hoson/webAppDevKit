#ifndef AddressTree
#define AddressTree

#include "../AddressNode/DomainNode/DomainNode.h"
#include "../RequestedRoute/RequestedDomain/RequestedDomain.h"
#include "../../../Apps/AppConfig/RouteDeployment/RouteDeployment.h"
#include <optional>

class AddressTree
{
	public: 
        void RouteRequest(
            const drogon::HttpRequestPtr&,
            drogon::HttpResponsePtr&
        );

        AddressNode* GetFinalAddressNode(RouteDeployment&);


    private:
        std::vector<DomainNode> RootNodes;

};


#endif