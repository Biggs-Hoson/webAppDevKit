#ifndef routeConstructorContext
#define routeConstructorContext

#include "../RoutingContext.h"


class RouteConstructorContext : public RoutingContext
{
    public:
        RouteConstructorContext(
            AppRouteDeployment&,
            AddressNodeChildren*
        );

        // Do this by Constructing AddressNodes
        void HandleNotFound() override;
    
        AddressNode* GetFinalAddresesNodePtr();

    protected:
        AddressNode* CurrentNode = nullptr;

        AddressNodeChildren* InitialAddressTree;

        // Match Only static MatchCriteria, reject fail if at AddressNode.AppNode == true or if child routes not empty
        bool CheckMatch(AddressNode*) override;

        // return current Node to be converted to an AppNode
        bool ResolveWithCurrentNode(AddressNode*) override;

    private:
        void ConstructRoute();

};

#endif