#ifndef routeConstructorContext
#define routeConstructorContext

#include "../RoutingContext.h"

#include "../../AddressNodeChildren/AddressTree/AddressTree.h"

class RouteConstructorContext : public RoutingContext
{
    public:
        RouteConstructorContext(
            AppRouteDeployment&,
            AddressTree*
        );

        // Do this by Constructing AddressNodes
        void HandleNotFound() override;
    
        AddressNode* GetFinalAddresesNodePtr();

    protected:
        AddressNode* CurrentNode = nullptr;

        AddressTree* InitialAddressTree;

        // Match Only static MatchCriteria, reject fail if at AddressNode.AppNode == true or if child routes not empty
        bool CheckMatch(AddressNode*) override;

        // return current Node to be converted to an AppNode
        bool ResolveWithCurrentNode(AddressNode*) override;

        bool RoutingInPath();

};

#endif