#include "RouteNodeAddress.h"

#include "../../../ComponentFunctions/UtilityFunctions/UtilityFunctions.h"

RouteNodeAddress::RouteNodeAddress(std::string addressString)
{
    // Split address on first / to get domain and  path
    std::size_t hostEnd = addressString.find('/');
    int routeLength = addressString.size();

    if (hostEnd!=std::string::npos)
    {
        std::string pathString = addressString.substr(hostEnd, routeLength - hostEnd);

        PathAddress = SplitStringOnChar(pathString, '/');
    }
    else
    {
        // No "/" found in path, route to the domain node only
        hostEnd = routeLength;
    }

    std::string domainString = addressString.substr(0, hostEnd);

    DomainAddress = SplitStringOnChar(domainString, '.');

    // Confirm all values are valid strings

    SetDomainMatch(true);
};

bool RouteNodeAddress::MatchRequest(MatchCriteria* criteria)
{
    if(*CurrentSegment == criteria->GetMatchString())
    {
        if (DomainMatch)
        {
            CurrentSegment--;
        }
        else {
            CurrentSegment++;
        }

        return true;
    }

    return false;
};

bool RouteNodeAddress::RoutingComplete()
{
    return CurrentSegment == FinalSegment;
};

void RouteNodeAddress::SetDomainMatch(bool domain)
{
    if (domain)
    {
        CurrentSegment = DomainAddress.end();
        FinalSegment = DomainAddress.begin();
    }
    else
    {
        CurrentSegment = PathAddress.begin();
        FinalSegment = PathAddress.end();
    }
}