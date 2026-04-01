#include <string>

#include "MatchClass.h"

MatchStaticPath::MatchStaticPath(const std::string& _path)
	: Path(_path), PathLength(Path.size()) { };


int MatchStaticPath::MatchRequest(std::string& _testPath) {
	if (_testPath.rfind(Path, 0) != 0) {
    	return 0;
    }
    
    if (_testPath[PathLength] == '/')
    {
    	return PathLength + 1;
    }
    
    return PathLength;
};