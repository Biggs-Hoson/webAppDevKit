#include "RouteNode.h"


RouteNode::RouteNode(
	Json::Value& _nodeData)
{
    NodeRouteSection = PATH;

    std::string path = _nodeData["path"].asString();

    // Select Match Object, for now stick to static paths
    RouteMatchObj = std::make_unique<MatchStaticPath>(path);

	Json::Value& subRoutesJson = _nodeData["subRoutes"];

	// Construct subpaths
	if (!subRoutesJson.isArray()) {
    	throw std::make_pair(500, "Server RouteMap is badly formatted.");
    }

    for (Json::ArrayIndex i = 0; i < subRoutesJson.size(); ++i) {
        SubRoutes.push_back(RouteNode(
            subRoutesJson[i]
        ));
    }
};


int RouteNode::RouteRequest(const drogon::HttpRequestPtr& req, drogon::HttpResponsePtr& resp, RouteSection currentRouteSection, std::string& routingStr)
{
	if (currentRouteSection != NodeRouteSection)
    {
    	return 0;
	}
    
    int matchResult = RouteMatchObj->MatchRequest(routingStr);
    
    if (matchResult == 0){
    	// Match Unsuccessfull, return 0 to attempt next RouteNode
        return 0;
    }
    
    // Match Successful
    
    if (routingStr.size() == matchResult) // No More routingStr to match, if domain, move to routing path, if path resolve request
    {
    	if (NodeRouteSection == DOMAIN)
        {
        	// Check if there is any path and route it if needed
            std::string path = req->getPath();
            
            if (path.size() > 0 && path != "/")
            {
                std::string path = req->getPath();

            	// Route Path
            	return RouteRemainingRequest(req, resp, PATH, path);
            
            }
        }
        
        return ResolveRequest(req, resp);
    }
    
    std::string remainingRoute = GetRemainingRoute(routingStr, matchResult);
    
	return RouteRemainingRequest(req, resp, NodeRouteSection, remainingRoute);
};

std::string RouteNode::GetRemainingRoute(std::string _routingStr, int matchedCharacterCount)
{
	// For paths only right now
    
    return _routingStr.substr(matchedCharacterCount);
}

int RouteNode::ResolveRequest(const drogon::HttpRequestPtr& req, drogon::HttpResponsePtr& resp)
{
    resp->setContentTypeCode(drogon::CT_TEXT_HTML);
    resp->setBody("<html> Endpoint found at path: " + req->getPath() + "</html>");
    
    return 200;
};

int RouteNode::RouteRemainingRequest(const drogon::HttpRequestPtr& req, drogon::HttpResponsePtr& resp, RouteSection currentRouteSection, std::string& routingStr)
{
	for (RouteNode& subRoute : SubRoutes){
		int responseCode = subRoute.RouteRequest(req, resp, currentRouteSection, routingStr);
		if (responseCode != 0) {
			return responseCode;
		}
	}

    return 404;
}
