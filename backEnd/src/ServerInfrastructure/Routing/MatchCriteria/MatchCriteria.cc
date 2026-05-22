#include <string>

#include "MatchCriteria.h"


MatchStaticString::MatchStaticString(const std::string _matchString)
	: MatchString(_matchString)  { };

bool MatchStaticString::MatchRequest(
    std::vector<std::string>::iterator& sectionIterrator) {
    return *sectionIterrator == MatchString;
};

MatchAny::MatchAny() {};

bool MatchAny::MatchRequest(
    std::vector<std::string>::iterator&) {

    return true;
};