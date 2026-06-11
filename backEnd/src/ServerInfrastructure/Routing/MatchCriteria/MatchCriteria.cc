#include <memory>
#include <string>

#include "MatchCriteria.h"


MatchCriteria::MatchCriteria(std::string _matchString)
{
    MatchString = _matchString;
}

std::string MatchCriteria::GetMatchString()
{
    return MatchString;
}

MatchStaticString::MatchStaticString(const std::string _matchString)
	: MatchCriteria(_matchString)  { };

bool MatchStaticString::MatchRequest(
    std::vector<std::string>::iterator& sectionIterrator) {
    return *sectionIterrator == MatchString;
};

MatchAny::MatchAny()
: MatchCriteria("*") {};

bool MatchAny::MatchRequest(
    std::vector<std::string>::iterator&) {

    return true;
};

static std::unique_ptr<MatchCriteria> GetMatchCriteraPtr(std::string matchCriteraString)
{
    if (matchCriteraString == "*")
    {
        return std::make_unique<MatchAny>();
    }
    else {
        return std::make_unique<MatchStaticString>(matchCriteraString);
    }
}