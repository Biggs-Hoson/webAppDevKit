#ifndef domainNode
#define domainNode

#include "../AddressNode.h"

class DomainNode : public AddressNode
{
	public: 
        void RoutePath(RoutingContext*);

    private:
        AddressNodeChildren PathRoutes;
};


#endif