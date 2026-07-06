#include "RoutingContext.h"

#include <optional>

#include "../AddressNode/DomainNode/DomainNode.h"
#include "../../../ComponentFunctions/UtilityFunctions/UtilityFunctions.h"



RoutingContext::RoutingContext(
    std::string _domain,
    std::string _path,
    AddressNodeChildren* AddressNodeChildrenPtr)
{
    DomainSplit = SplitStringOnChar(_domain, '.');
    PathSplit = SplitStringOnChar(_path, '/');

    if (dynamic_cast<DomainNodeChildren*>(AddressNodeChildrenPtr) == nullptr)
    {
        SetupPathRouting();
    }
    else
    {
        CurrentSegment = --DomainSplit.end();
        FinalSegment = --DomainSplit.begin();
    }

}


// Return type:
// false = does not match, routing system needs to try next AddressNode
// true = matches and is final part of path
// std::nullopt = matches but there is more rpath to route
std::optional<bool> RoutingContext::MatchNode(AddressNode* _node) // Use Node Type to determine routing situation
{
    if(!CheckMatch(_node)) // Matching fails
    {
        return false;
    }

    IncrementSegment();

    // Grab any new context from current node

    if (!RoutingComplete())
    {
        return std::nullopt;
    }

    DomainNode* _domainNode = dynamic_cast<DomainNode*>(_node);

    if (_domainNode != nullptr && !PathSplit.empty())
    {
        // Route in path:
        SetupPathRouting();

        _domainNode->RoutePath(this);

        return true;
    }
    
    return ResolveWithCurrentNode(_node);
}

bool RoutingContext::RoutingInPath()
{
    return PathSplit.end() == FinalSegment; 
}

void RoutingContext::IncrementSegment()
{
    if (RoutingInPath())
    {
        CurrentSegment++;
    }
    else {
        CurrentSegment--;
    }
}

void RoutingContext::SetupPathRouting()
{
    CurrentSegment = PathSplit.begin();
    FinalSegment = PathSplit.end();
}

bool RoutingContext::RoutingComplete()
{
    return CurrentSegment == FinalSegment;
}

bool RoutingContext::CheckMatch(AddressNode* _node)
{
    std::string matchCriteria = _node->GetMatchCritera();

    if(matchCriteria == "*") // Handle Wildcard
    {
        CurrentSegment = FinalSegment;

        if (RoutingInPath())
        {
            CurrentSegment--;
        }
        else 
        {
            CurrentSegment++;
        }

        return true;
    }

    return *CurrentSegment == matchCriteria;
}