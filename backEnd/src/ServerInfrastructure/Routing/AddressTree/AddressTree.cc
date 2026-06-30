#include "AddressTree.h"

void AddressTree::RouteRequestInTree(
    RoutingContext* routeContext)
{
    for (std::unique_ptr<AddressNode>& subRoutePtr : Routes){
		if (subRoutePtr->RouteRequest(routeContext)) {
			return;
		}
	}
};

bool AddressTree::Empty()
{
    return Routes.size() == 0;
}

//throw std::pair(503, "Server routing is not functioning currently.");

