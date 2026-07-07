#include "AddressNodeChildren.h"
#include "../AddressNode/AddressNode.h"
#include "../RoutingContext/RoutingContext.h"
#include <memory>
#include <string>

void AddressNodeChildren::RouteRequestInChildren(
    RoutingContext* routeContext)
{
    for (std::unique_ptr<AddressNode>& subRoutePtr : Routes){
		if (subRoutePtr->RouteRequest(routeContext)) {
			return;
		}
	}

	routeContext->HandleNotFound();
};

bool AddressNodeChildren::Empty()
{
    return Routes.size() == 0;
}

AddressNode* AddressNodeChildren::CreateSubRoute(AddressNodeTemplate& _subNodeTemplate)
{
    Routes.push_back(std::make_unique<AddressNode>(_subNodeTemplate));

	return Routes.back().get();
};

AddressNode* AddressNodeChildren::CreateSubRoute(std::string matchCritera)
{
    Routes.push_back(std::make_unique<AddressNode>(matchCritera));

	return Routes.back().get();
};

void AddressNodeChildren::Explore(int depth)
{
	CallIn();

	std::cout << std::string(depth, '-') << Routes.size() << std::endl;

	for(std::unique_ptr<AddressNode>& node : Routes)
	{
		node->Explore(++depth);
	}
}

void AddressNodeChildren::CallIn()
{
	std::cout << "AddressNodeChildSet" << std::endl;
}