#include "./RouteConstructorContext.h"

#include "../../AddressNode/DomainNode/DomainNode.h"

RouteConstructorContext::RouteConstructorContext(
    AppRouteDeployment& routeDeploymentConfig
) : RoutingContext(
        routeDeploymentConfig.GetDomain(), 
        routeDeploymentConfig.GetPath())
{}

void RouteConstructorContext::HandleNotFound()
{
    // Called when RouteConstructorContext arrives at an end route.
    // Handle by constructing AddressNode and DomainNodes in children

    if(PathSplit.end() != FinalSegment) // still some domain to route
    {
        DomainNode* _domainNode = dynamic_cast<DomainNode*>(CurrentNode);
        
        while(CurrentSegment != FinalSegment)
        {
            _domainNode = _domainNode->CreateSubDomain(*CurrentSegment);

            if (_domainNode == nullptr)
            {
                throw "Domain node constructed, but cast to domain Node failed.";
            }

            CurrentSegment--;
        }

        CurrentNode = _domainNode;

        CurrentSegment = PathSplit.begin();
        FinalSegment = PathSplit.end();
    }

    while(CurrentSegment != FinalSegment)
    {
        CurrentNode = CurrentNode->CreateSubRoute(*CurrentSegment);

        if (CurrentNode == nullptr)
        {
            throw "Path node was not constructed.";
        }

        CurrentSegment++;
    }
}

// Match Only static MatchCriteria, reject fail if at AddressNode.AppNode == true;
bool RouteConstructorContext::CheckMatch(AddressNode* _node)
{
    MatchCriteria* match = _node->GetMatchCritera();

    MatchStaticString* staticMatch = dynamic_cast<MatchStaticString*>(match);

    if (staticMatch == nullptr)
    {
        // MatchCriteria is not static
        return false;
    }

    if (staticMatch->GetMatchString() != *CurrentSegment)
    {
        // MatchCriteria does not match
        return false;
    }

    if (_node->IsAppNode() && FinalSegment == PathSplit.end())
    {
        throw "Route already contains an AppNode in the path";
    }
    
    CurrentNode = _node;
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