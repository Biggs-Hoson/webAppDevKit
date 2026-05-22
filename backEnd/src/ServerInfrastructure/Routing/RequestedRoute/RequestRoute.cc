#include "RequestedRoute.h"

#include <sstream>

RequestedRoute::RequestedRoute(std::string requestString)
{
    std::vector<std::string> HostVec;
    std::stringstream ss(requestString);
    std::string item;

    while (std::getline(ss, item, '.')) {
        if (!item.empty())
            HostVec.push_back(item);
    }
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
