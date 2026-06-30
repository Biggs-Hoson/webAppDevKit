#ifndef addressNodeAddress
#define addressNodeAddress

#include <string>
#include <vector>

#include "../MatchCriteria/MatchCriteria.h"

// Introduce some way to mark an address as relative

class AddressNodeAddress
{
    public:
        AddressNodeAddress(std::string);

        bool RoutingComplete();

        bool MatchRequest(MatchCriteria*);

        void SetDomainMatch(bool);
    
    private:
        std::vector<std::string> PathAddress;

        std::vector<std::string> DomainAddress;

        std::vector<std::string>::iterator CurrentSegment;

        std::vector<std::string>::iterator FinalSegment;

        bool DomainMatch;
};


#endif