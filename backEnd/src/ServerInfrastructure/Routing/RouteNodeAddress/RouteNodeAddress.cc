#include "AddressNodeAddress.h"

#include "../../../ComponentFunctions/UtilityFunctions/UtilityFunctions.h"

AddressNodeAddress::AddressNodeAddress(std::string addressString)
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

bool AddressNodeAddress::MatchRequest(MatchCriteria* criteria)
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

bool AddressNodeAddress::RoutingComplete()
{
    return CurrentSegment == FinalSegment;
};

void AddressNodeAddress::SetDomainMatch(bool domain)
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