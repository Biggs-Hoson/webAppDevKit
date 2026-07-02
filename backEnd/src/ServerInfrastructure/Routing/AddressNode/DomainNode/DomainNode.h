#ifndef domainNode
#define domainNode

#include "../AddressNode.h"

class DomainNode : public AddressNode
{
	public: 
        DomainNode(std::string);

        void RoutePath(RoutingContext*);

        DomainNode* CreateSubDomain(std::string);

        AddressNode* CreateSubRoute(std::string) override;

        void Explore(int) override;

    protected:
        AddressNode* CreateSubRoute(AddressNodeTemplate&) override;

    private:
        AddressNodeChildren PathRoutes;


};


#endif