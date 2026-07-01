#include "DomainNode.h"

void DomainNode::RoutePath(RoutingContext* _route)
{
    PathRoutes.RouteRequestInChildren(_route);
};