#include "./RouteConstructorContext.h"

#include "../../AddressNode/DomainNode/DomainNode.h"

RouteConstructorContext::RouteConstructorContext(
    AppRouteDeployment& routeDeploymentConfig,
    AddressNodeChildren* initialTree
) : RoutingContext(
        routeDeploymentConfig.GetDomain(), 
        routeDeploymentConfig.GetPath(),
        initialTree),
        
    InitialAddressTree(initialTree)
{
    InitialAddressTree->RouteRequestInChildren(this);
}

void RouteConstructorContext::HandleNotFound()
{
    // Called when RouteConstructorContext arrives at an end route.
    // Handle by constructing AddressNode and DomainNodes in children
    if (CurrentNode == nullptr)
    {
        CurrentNode = InitialAddressTree->CreateSubRoute(*CurrentSegment);

        IncrementSegment();
    }

    ConstructRoute();

    if(RoutingInPath()) // Segment above was path segment
    {        
        return;        
    }

    SetupPathRouting();

    if (RoutingComplete())
    {
        return;
    }

    // Set up first path route
    DomainNode* currentDomain = dynamic_cast<DomainNode*>(CurrentNode);

    if (currentDomain == nullptr)
    {
        throw "Domain Cast failed when switching to path";
    }

    CurrentNode = currentDomain->ConstructFirstPath(*CurrentSegment);

    CurrentSegment++;

    ConstructRoute();
}

// Match Only static MatchCriteria, reject fail if at AddressNode.AppNode == true;
bool RouteConstructorContext::CheckMatch(AddressNode* _node)
{
    std::string matchCritera = _node->GetMatchCritera();

    if (matchCritera == "*" || matchCritera != *CurrentSegment)
    {
        return false;
    }

    if (_node->IsAppNode() && RoutingInPath())
    {
        throw "Route already contains an AppNode in the path";
    }
    
    CurrentNode = _node;

    return true;
}

// return current Node to be converted to an AppNode
bool RouteConstructorContext::ResolveWithCurrentNode(AddressNode* _node)
{
    CurrentNode = _node;

    return true;
}

AddressNode* RouteConstructorContext::GetFinalAddresesNodePtr()
{
    return CurrentNode;
}

void RouteConstructorContext::ConstructRoute()
{
    while(!RoutingComplete())
    {
        CurrentNode = CurrentNode->CreateSubRoute(*CurrentSegment);

        if (CurrentNode == nullptr)
        {
            throw "Node Construction failure";
        }

        IncrementSegment();
    }
}