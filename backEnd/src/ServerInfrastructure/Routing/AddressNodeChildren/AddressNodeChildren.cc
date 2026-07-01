#include "AddressNodeChildren.h"
#include "../AddressNode/AddressNode.h"
#include "../RoutingContext/RoutingContext.h"
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
