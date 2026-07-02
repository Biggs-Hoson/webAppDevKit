#include "AddressTree.h"
#include "../../AddressNode/DomainNode/DomainNode.h"

#include <memory>

AddressNode* AddressTree::CreateDomain(std::string matchCritera)
{    
    Routes.push_back(std::make_unique<DomainNode>(matchCritera));

	return Routes.back().get();
};