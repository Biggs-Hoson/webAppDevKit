#include <string>

#include "MatchClass.h"


MatchStaticPath::MatchStaticPath(const std::string _path)
	: Path(_path), PathLength(Path.size()) { };

int MatchStaticPath::MatchRequest(std::string& _testPath) {
    
    if (_testPath.compare(0, PathLength, Path) != 0) {
        return 0;
    }
    
    if (_testPath[PathLength] == '/')
    {
    	return PathLength + 1;
    }
    
    return 0;
};


MatchStaticDomain::MatchStaticDomain(const std::string _domain)
	: Domain(_domain), DomainLength(Domain.size()) { };

int MatchStaticDomain::MatchRequest(std::string& _testDomain)
{
    if (_testDomain.compare(_testDomain.size() - DomainLength, DomainLength, Domain) != 0)
    {
        return 0;
    }
    
    return DomainLength;

    if (_testDomain[_testDomain.size() - DomainLength] == '.')
    {
    	return DomainLength + 1;
    }
    
};