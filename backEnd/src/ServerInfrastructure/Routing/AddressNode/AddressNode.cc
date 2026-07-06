#include "AddressNode.h"

#include "../RoutingContext/RoutingContext.h"
#include <string>

// ---------- Constructor and Setup Functions ---------- //

AddressNode::AddressNode(AddressNodeTemplate& _nodeTemplate)
: MatchCritera(_nodeTemplate.GetMatchCritera())
{
    // Set Match Critera
    StructureFromTemplate(_nodeTemplate);
}

AddressNode::AddressNode(std::string criteriaString)
: MatchCritera(criteriaString) {}


void AddressNode::SetMatchCritera(std::string criteriaString)
{
    MatchCritera = criteriaString;
}

// Used so can create with an AppNodeTemplate, that doesn't have a match string
void AddressNode::StructureFromTemplate(AddressNodeTemplate& _nodeTemplate)
{
    // Set Endpoint
    // Endpoint = ...
    
    // Create subroutes
    for(AddressNodeTemplate& subRoute : _nodeTemplate.GetSubRoutes())
    {
        CreateSubRoute(subRoute);
    }
};

// ---------- Routing Function ---------- //

bool AddressNode::RouteRequest(RoutingContext* routeContext)
{
    std::optional<bool> routingState = routeContext->MatchNode(this);

    // Match Request
    if (routingState.has_value()){
        // routingState.value ==
        // false:  Match Unsuccessful, return false to attempt next AddressNode
        // true:  Routing Complete, return true to end Routing Request
        return routingState.value();
    }

    RouteRequestInChildren(routeContext);

    return true; // Routing Performed, no more action to take
}

std::string AddressNode::GetMatchCritera()
{
    return MatchCritera;
}

bool AddressNode::IsAppNode()
{
    return AppNode;
}

// ---------- Endpoint functions ---------- //

void AddressNode::CallIn()
{
    std::cout << GetMatchCritera() << std::endl;
}