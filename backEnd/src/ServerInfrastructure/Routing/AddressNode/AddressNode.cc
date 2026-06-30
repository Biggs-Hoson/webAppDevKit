#include "AddressNode.h"

#include "../RoutingContext/RoutingContext.h"

// ---------- Constructor and Setup Functions ---------- //

AddressNode::AddressNode(AddressNodeTemplate& _nodeTemplate)
{
    // Set Match Critera
    MatchCriteraPtr = MatchCriteria::GetMatchCriteraPtr(_nodeTemplate.GetMatchCritera());

    StructureFromTemplate(_nodeTemplate);
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
        // truee:  Routing Complete, return true to end Routing Request
        return routingState.value();
    }

    for (std::unique_ptr<AddressNode>& subRoutePtr : SubRoutes){
		if (subRoutePtr->RouteRequest(routeContext)) {
			return true;
		}
	}

    return true; // Routing Performed, no more actiosn to take
}


// ---------- Endpoint functions ---------- //

void AddressNode::CreateSubRoute(AddressNodeTemplate _subNodeTemplate)
{
    SubRoutes.push_back(std::make_unique<AddressNode>(_subNodeTemplate));
};

