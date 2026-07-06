#ifndef domainNode
#define domainNode

#include "../AddressNode.h"
#include "../../AddressNodeChildren/DomainNodeChildren/DomainNodeChildren.h"

class DomainNode : public AddressNode, public DomainNodeChildren
{
	public: 
        DomainNode(std::string);

        void RoutePath(RoutingContext*);

        void Explore(int) override;

        AddressNode* ConstructFirstPath(std::string);

        AddressNode* CreateSubRoute(AddressNodeTemplate&) override; // Overriden here so AppNodeTemplate doesn't create pathNodes in the DomainNodeChildren

    protected:

    private:
        AddressNodeChildren PathRoutes;


};


#endif