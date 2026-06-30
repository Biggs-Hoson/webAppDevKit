#ifndef routingContext
#define routingContext

#include <string>
#include <vector>
#include <optional>

#include "../MatchCriteria/MatchCriteria.h"
#include "../AddressNode/AddressNode.h"

/*
    The RoutingContext holds the nessecary context to handle a request 


*/
class RoutingContext
{
    public:
        //RoutingContext(std::string) // combined domain and path

        RoutingContext(std::string, std::string); // combined domain and path

        virtual std::optional<bool> MatchNode(AddressNode*);
    
    protected:
        std::vector<std::string> DomainSplit;
        std::vector<std::string> PathSplit;

        std::vector<std::string>::iterator CurrentSegment;
        std::vector<std::string>::iterator FinalSegment;

        bool RoutingDomain = true;

        // Virtual Functions:

        virtual bool CheckMatch(AddressNode*) = 0;

        virtual bool ResolveWithCurrentNode(AddressNode*) = 0;

};

#endif