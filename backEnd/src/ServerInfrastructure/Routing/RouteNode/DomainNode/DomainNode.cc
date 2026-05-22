#include "DomainNode.h"

int DomainNode::ResolveRequest(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp
)
{
    // Check if there is any path and route it if needed
    std::string path = req->getPath();
    
    if (path.size() > 0 && path != "/")
    {
        RequestedPath pathRequest(path);

        // Route Path
        return RoutePath(req, resp, &pathRequest);
    }
    
    return HitEndpoint(req, resp);
}


bool DomainNode::MatchRequest(
    RequestedRoute* _route
)
{
    return _route->MatchRequest(MatchCritera.get());
};

bool DomainNode::RouteRequestInSubroutes(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp,
    RequestedRoute* _route
)
{
    for (DomainNode& subdomain : SubDomainNodes){
		int responseCode = subdomain.RouteRequest(req, resp, _route);
		if (responseCode != 0) {
			return responseCode;
		}
	}

    return 404;
};


int DomainNode::RoutePath(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp, 
    RequestedRoute* _route
)
{
    for (PathNode& subPath : PathNodes){
		int responseCode = subPath.RouteRequest(req, resp, _route);
		if (responseCode != 0) {
			return responseCode;
		}
	}

    return 404;
};


int DomainNode::HitEndpoint(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp
)
{
    resp->setContentTypeCode(drogon::CT_TEXT_HTML);
    resp->setBody("<html> Endpoint found at host: " + req->getHeader("Host") + "</html>");

    resp->setBody("<html> Hello Mum! </html>");
    
    return 200;
};