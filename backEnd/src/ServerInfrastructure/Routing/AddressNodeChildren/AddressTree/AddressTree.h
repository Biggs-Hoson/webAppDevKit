#ifndef addressTree
#define addressTree

#include "../AddressNodeChildren.h"

class AddressTree : public AddressNodeChildren
{
    public:
        AddressNode* CreateDomain(std::string);
};


#endif