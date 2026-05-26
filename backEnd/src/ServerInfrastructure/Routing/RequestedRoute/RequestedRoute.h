#ifndef requestedRoute
#define requestedRoute

#include <string>
#include <vector>

#include "../MatchCriteria/MatchCriteria.h"

class RequestedRoute
{
    public:
        RequestedRoute(std::string, char);

        bool RoutingComplete();

        bool MatchRequest(MatchCriteria*);

        bool MatchRequest(std::vector<MatchCriteria*>);
    
    protected:
        std::vector<std::string> RequestSplit; 

        std::vector<std::string>::iterator CurrentSegment;
        std::vector<std::string>::iterator FinalSegment;

        virtual void IncrementSegment() = 0;
};


#endif