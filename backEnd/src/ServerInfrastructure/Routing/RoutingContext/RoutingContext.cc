#include "RoutingContext.h"

#include "../../../ComponentFunctions/UtilityFunctions/UtilityFunctions.h"


RoutingContext::RoutingContext(
    std::string _domain,
    std::string _path)
{
    DomainSplit = SplitStringOnChar(_domain, ".");
    PathSplit = SplitStringOnChar(_path, "/");

    CurrentSegment = DomainSplit.begin();
    FinalSegment = DomainSplit.end();
}

std::optional<bool> MatchNode(AddressNode* _node) // Use Node Type to determine routing situation
{
    MatchCriteria* matchCriteriaPtr = _node->GetMatchCritera();

    if(!) // Matching fails
    {
        return false;
    }

    if (CurrentSegment == FinalSegment)
    {
        if (RoutingDomain)
        {
            RoutingDomain == false;

            _node. 
        }
        else
        {
            // Resolve with current node
        }


        return true;
    }

    // Grab any new context

    return nullopt_t;
}