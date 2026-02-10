#ifndef routing
#define routing

#include <vector>
#include <memory>

class RouteNode {

public: 
    std::vector<std::unique_ptr<RouteNode>> subPath;
};

#endif