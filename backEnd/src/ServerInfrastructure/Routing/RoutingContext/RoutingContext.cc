#include "RoutingContext.h"

#include "../../../ComponentFunctions/UtilityFunctions/UtilityFunctions.h"
#include <optional>


RoutingContext::RoutingContext(
    std::string _domain,
    std::string _path)
{
    DomainSplit = SplitStringOnChar(_domain, '.');
    PathSplit = SplitStringOnChar(_path, '/');

    CurrentSegment = DomainSplit.end();
    FinalSegment = DomainSplit.begin();
}

std::optional<bool> RoutingContext::MatchNode(AddressNode* _node) // Use Node Type to determine routing situation
{
    if(!CheckMatch(_node)) // Matching fails
    {
        return false;
    }

    if (RoutingDomain)
    {
        CurrentSegment--;

        if (CurrentSegment == FinalSegment)
        {
            if (PathSplit.empty())
            {
                return ResolveWithCurrentNode(_node);
            }

            RoutingDomain = false;
            CurrentSegment = PathSplit.begin();
            FinalSegment = PathSplit.end();
        
            return _node->RouteRequest(this);
        }
    }
    else {
        CurrentSegment++;
    
        if (CurrentSegment == FinalSegment)
        {
            return ResolveWithCurrentNode(_node);
        }
    }

    // Grab any new context from current node

    return std::nullopt;
}