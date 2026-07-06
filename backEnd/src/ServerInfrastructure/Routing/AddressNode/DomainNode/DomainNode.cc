#include "DomainNode.h"

DomainNode::DomainNode(std::string matchCritera)
 : AddressNode(matchCritera) {}
 
void DomainNode::RoutePath(RoutingContext* _route)
{
    PathRoutes.RouteRequestInChildren(_route);
};


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

AddressNode* DomainNode::ConstructFirstPath(std::string _matchCriteria)
{
    return PathRoutes.CreateSubRoute(_matchCriteria);
}

AddressNode* DomainNode::CreateSubRoute(AddressNodeTemplate& _appTemplate)
{
    return PathRoutes.CreateSubRoute(_appTemplate);   
}