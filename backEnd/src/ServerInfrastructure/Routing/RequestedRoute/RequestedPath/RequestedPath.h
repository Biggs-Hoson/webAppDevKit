#ifndef requestedPath
#define requestedPath

#include "../RequestedRoute.h"

class RequestedPath : public RequestedRoute
{
    public:
        RequestedPath(std::string);

    protected:
        void IncrementSegment() override;
};

#endif