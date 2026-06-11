#ifndef pathNode
#define pathNode

#include "../RouteNode.h"

class PathNode : public RouteNode
{
	public: 
		PathNode();

		int ResolveRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		) = 0;

	private:
		std::vector<PathNode> SubPaths;
};


#endif