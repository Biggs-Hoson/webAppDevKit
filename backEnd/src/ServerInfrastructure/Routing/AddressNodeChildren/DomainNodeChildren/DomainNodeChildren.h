#ifndef domainNodeChildren
#define domainNodeChildren

#include "../AddressNodeChildren.h"

#include <optional>
#include <memory>

class DomainNode;

class DomainNodeChildren : public virtual AddressNodeChildren
{
	public: 
        AddressNode* CreateSubRoute(std::string) override;

    protected:
};


#endif