#ifndef pathNode
#define pathNode

#include "../RouteNode.h"

class PathNode : public RouteNode
{
	public: 

		int ResolveRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		) = 0;

	protected:
		bool MatchRequest(
			RequestedRoute*
		);

		bool RouteRequestInSubroutes(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
		);

	private:
		std::unique_ptr<MatchCriteria> MatchCritera;

		std::vector<PathNode> SubPaths;
};


#endif