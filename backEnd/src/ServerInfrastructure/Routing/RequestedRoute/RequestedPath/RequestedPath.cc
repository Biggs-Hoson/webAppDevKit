#include "RequestedPath.h"


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