#include "./DomainNodeChildren.h"
#include "../../AddressNode/DomainNode/DomainNode.h"

AddressNode* DomainNodeChildren::CreateSubRoute(std::string matchCritera)
{
    Routes.push_back(std::make_unique<DomainNode>(matchCritera));

	return Routes.back().get();
};