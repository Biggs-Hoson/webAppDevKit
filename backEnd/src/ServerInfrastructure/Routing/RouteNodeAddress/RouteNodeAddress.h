#ifndef routeNodeAddress
#define routeNodeAddress

#include <string>
#include <vector>

// Introduce some way to mark an address as relative

class RouteNodeAddress
{
    public:
        RouteNodeAddress(std::string);
    
    private:
        std::vector<std::string> PathAddress;

        std::vector<std::string> DomainAddress;
};


#endif