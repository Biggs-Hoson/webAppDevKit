#include "RoutingContext.h"

#include <optional>

#include "../AddressNode/DomainNode/DomainNode.h"
#include "../../../ComponentFunctions/UtilityFunctions/UtilityFunctions.h"



RoutingContext::RoutingContext(
    std::string _domain,
    std::string _path)
{
    DomainSplit = SplitStringOnChar(_domain, '.');
    PathSplit = SplitStringOnChar(_path, '/');

    CurrentSegment = DomainSplit.end();
    FinalSegment = DomainSplit.begin();
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

    DomainNode* _domainNode = dynamic_cast<DomainNode*>(_node);

    if (_domainNode != nullptr)
    {
        CurrentSegment--;
    }
    else {
        CurrentSegment++;
    }

    // Grab any new context from current node

    if (CurrentSegment != FinalSegment)
    {
        return std::nullopt;
    }

    if (_domainNode != nullptr && !PathSplit.empty())
    {
        // Route in path:
        CurrentSegment = PathSplit.begin();
        FinalSegment = PathSplit.end();

        _domainNode->RoutePath(this);

        return true;
    }
    
    return ResolveWithCurrentNode(_node);
}