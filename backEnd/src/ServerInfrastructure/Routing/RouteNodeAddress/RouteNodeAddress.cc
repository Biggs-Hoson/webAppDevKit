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
};