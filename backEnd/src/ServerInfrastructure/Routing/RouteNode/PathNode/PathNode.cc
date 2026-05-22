#include "PathNode.h"

int PathNode::ResolveRequest(
	const drogon::HttpRequestPtr& req,
	drogon::HttpResponsePtr& resp
)
{
	resp->setContentTypeCode(drogon::CT_TEXT_HTML);
    resp->setBody("<html> Endpoint found at host: " + req->getHeader("Host") + "</html>");

    resp->setBody("<html> Hello Mum! </html>");
    
    return 200;
};


bool PathNode::MatchRequest(
	RequestedRoute* _route
)
{
	return _route->MatchRequest(MatchCritera.get());
};

bool PathNode::RouteRequestInSubroutes(
	const drogon::HttpRequestPtr& req,
	drogon::HttpResponsePtr& resp, 
	RequestedRoute* _route
)
{
	for (PathNode& subPath : SubPaths){
		int responseCode = subPath.RouteRequest(req, resp, _route);
		if (responseCode != 0) {
			return responseCode;
		}
	}

    return 404;
};