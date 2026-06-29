#include "RequestedRoute.h"

#include "../../../ComponentFunctions/UtilityFunctions/UtilityFunctions.h"

RequestedRoute::RequestedRoute(std::string requestString, char splitChar)
{
    RequestSplit = SplitStringOnChar(requestString, splitChar);
};

bool RequestedRoute::RoutingComplete()
{
    return CurrentSegment == FinalSegment;
}

bool RequestedRoute::MatchRequest(MatchCriteria* criteria)
{
    if (criteria->MatchRequest(CurrentSegment))
    {
        IncrementSegment();
        
        return true;
    }

    return false;
}

bool RequestedRoute::MatchRequest(std::vector<MatchCriteria*> criteriaVec)
{
    std::vector<std::string>::iterator InitialSegment = CurrentSegment;

    for (MatchCriteria* criteria : criteriaVec)
    {
        if (!criteria->MatchRequest(CurrentSegment))
        {
            CurrentSegment = InitialSegment;

            return false;
        }

        IncrementSegment();
    }

    return true;
}
