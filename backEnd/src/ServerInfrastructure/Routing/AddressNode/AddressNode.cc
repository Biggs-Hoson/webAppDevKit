#include "AddressNode.h"

#include "../RoutingContext/RoutingContext.h"

// ---------- Constructor and Setup Functions ---------- //

AddressNode::AddressNode(AddressNodeTemplate& _nodeTemplate)
{
    // Set Match Critera
    SetMatchCritera(_nodeTemplate.GetMatchCritera());

    StructureFromTemplate(_nodeTemplate);
}

AddressNode::AddressNode(std::string criteriaString)
{
    // Set Match Critera
    SetMatchCritera(criteriaString);
}


void AddressNode::SetMatchCritera(std::string criteriaString)
{
    MatchCriteraPtr = MatchCriteria::GetMatchCriteraPtr(criteriaString);
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

    void RouteRequestInChildren(RoutingContext*);

    return true; // Routing Performed, no more action to take
}

MatchCriteria* AddressNode::GetMatchCritera()
{
    return MatchCriteraPtr.get();
}

bool AddressNode::IsAppNode()
{
    return AppNode;
}

// ---------- Endpoint functions ---------- //

