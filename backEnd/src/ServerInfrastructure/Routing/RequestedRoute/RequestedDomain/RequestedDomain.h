#ifndef requestedDomain
#define requestedDomain

#include "../RequestedRoute.h"

class RequestedDomain : public RequestedRoute
{
    public:
        RequestedDomain(std::string);

    protected:
        void IncrementSegment() override;
};

#endif