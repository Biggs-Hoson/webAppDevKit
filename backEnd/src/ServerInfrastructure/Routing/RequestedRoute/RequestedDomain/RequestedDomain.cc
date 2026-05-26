#include "RequestedDomain.h"

RequestedDomain::RequestedDomain(std::string _domainString)
    : RequestedRoute(_domainString, '.')
{
    CurrentSegment = RequestSplit.end();
    FinalSegment = RequestSplit.begin();
};

void RequestedDomain::IncrementSegment()
{
    --CurrentSegment;
};