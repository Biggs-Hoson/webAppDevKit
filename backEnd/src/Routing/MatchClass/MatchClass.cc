#include <string>

#include "MatchClass.h"


MatchStaticString::MatchStaticString(const std::string _matchString)
	: MatchString(_matchString)  { };

bool MatchStaticString::MatchRequest(
    std::vector<std::string>::iterator& nextSection,
	std::vector<std::string>::iterator& finalSection) {
    return *nextSection == MatchString;
};