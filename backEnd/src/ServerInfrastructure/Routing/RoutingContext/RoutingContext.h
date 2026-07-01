#ifndef routingContext
#define routingContext

#include <string>
#include <vector>
#include <optional>

#include "../MatchCriteria/MatchCriteria.h"
#include "../AddressNode/AddressNode.h"

/*
    The RoutingContext holds the necessary context to handle a request 


*/
class RoutingContext
{
    public:
        //RoutingContext(std::string) // combined domain and path

        RoutingContext(std::string, std::string); // combined domain and path

        virtual std::optional<bool> MatchNode(AddressNode*);

        virtual void HandleNotFound() = 0;
    
    protected:
        std::vector<std::string> DomainSplit;
        std::vector<std::string> PathSplit;

        std::vector<std::string>::iterator CurrentSegment;
        std::vector<std::string>::iterator FinalSegment;

        // Virtual Functions:

        virtual bool CheckMatch(AddressNode*) = 0;

        virtual bool ResolveWithCurrentNode(AddressNode*) = 0;

};

#endif