#include "RequestedPath.h"
#include "../RequestedDomain/RequestedDomain.h"


RequestedPath::RequestedPath(std::string _domainString)
    : RequestedRoute(_domainString)
{
    CurrentSegment = RequestSplit.begin();
    FinalSegment = RequestSplit.end();
};

void RequestedPath::IncrementSegment()
{
    ++CurrentSegment;
};