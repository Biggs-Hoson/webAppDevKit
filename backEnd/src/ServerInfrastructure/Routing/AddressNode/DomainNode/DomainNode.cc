#include "DomainNode.h"

DomainNode::DomainNode(std::string matchCritera)
 : AddressNode(matchCritera) {}
 
void DomainNode::RoutePath(RoutingContext* _route)
{
    PathRoutes.RouteRequestInChildren(_route);
};

AddressNode* DomainNode::CreateSubRoute(AddressNodeTemplate& nodeTemplate)
{
    return PathRoutes.CreateSubRoute(nodeTemplate);
}

AddressNode* DomainNode::CreateSubRoute(std::string matchCritera)
{
    return PathRoutes.CreateSubRoute(matchCritera);
}

DomainNode* DomainNode::CreateSubDomain(std::string matchCritera)
{
    Routes.push_back(std::make_unique<DomainNode>(matchCritera));

    return dynamic_cast<DomainNode*>(Routes.back().get());
}

void DomainNode::Explore(int depth)
{
	CallIn();

	std::cout << std::string(depth, '-') << Routes.size() << std::endl;

	for(std::unique_ptr<AddressNode>& node : Routes)
	{
		node->Explore(++depth);
	}

    if(!PathRoutes.Empty())
    {
        PathRoutes.Explore(++depth);
    }
}