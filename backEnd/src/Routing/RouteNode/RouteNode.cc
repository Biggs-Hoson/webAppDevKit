#include "RouteNode.h"

constexpr struct JsonKeyNodeType {
    const char* key;
    RouteSection value;
} JsonKeyNodeTypeMap[] = {
    {"domain", RouteSection::DOMAIN},
    {"path", RouteSection::PATH}
};


RouteNode::RouteNode(Json::Value& _nodeData, RouteSection& parentType, std::string& currentRoute)
{
    bool typeFound;

    for (const auto& KeyType : JsonKeyNodeTypeMap) {
        if (_nodeData.isMember(KeyType.key)) {
            if (typeFound) {
                ThrowFormatError(500, "Ambiguous node type at: " + currentRoute);
            }
            typeFound = true;
            NodeRouteSection =KeyType.value;
        }
    }
    
    if (!typeFound)
    {
        ThrowFormatError(500, "No node type set at: " + currentRoute);
    }

    std::string NewRoute;
    std::string MatchCriteria;


    // This will need a rework when I introduce different Match criteria
    switch (NodeRouteSection) {
        case DOMAIN:

            MatchCriteria = _nodeData["domain"].asString();
            
            NewRoute = MatchCriteria + "." + currentRoute;

            if (parentType == PATH)
            {
                ThrowFormatError(500, "Cannot have domains node below path nodes at node: " + currentRoute);
            }

            // Select Match Object, for now stick to static paths
            RouteMatchObj = std::make_unique<MatchStaticString>(MatchCriteria);

            break;
        case PATH:

            MatchCriteria = _nodeData["path"].asString();
            
            NewRoute = currentRoute + "/" + MatchCriteria;

            // Select Match Object, for now stick to static paths
            RouteMatchObj = std::make_unique<MatchStaticString>(MatchCriteria);
            break;
    }


    if (_nodeData.isMember("subRoutes"))
    {
        SetSubRoutes(_nodeData["subRoutes"], NewRoute);
    }
};

void RouteNode::SetSubRoutes(Json::Value& _subRoutes, std::string& _newRoute)
{    
    // Construct subpaths
	if (!_subRoutes.isArray()) {
        ThrowFormatError();
    }

    for (Json::ArrayIndex i = 0; i < _subRoutes.size(); ++i) {
        SubRoutes.push_back(RouteNode(_subRoutes[i], NodeRouteSection, _newRoute));
    }
}

int RouteNode::RouteRequest(
const drogon::HttpRequestPtr& req,
drogon::HttpResponsePtr& resp,
RouteSection currentRouteSection, 
std::vector<std::string>::iterator& nextSection,
std::vector<std::string>::iterator& finalSection)
{
	if (currentRouteSection != NodeRouteSection)
    {
    	return 0;
	}

    if (!RouteMatchObj->MatchRequest(nextSection, finalSection)){
    	// Match Unsuccessful, return 0 to attempt next RouteNode
        return 0;
    }
    
    // Match Successful
    
    if (nextSection == finalSection) // No More routingStr to match, if domain, move to routing path, if path resolve request
    {
    	if (NodeRouteSection == DOMAIN) // This can be extracted with a std::func
        {
        	// Check if there is any path and route it if needed
            std::string path = req->getPath();
            
            if (path.size() > 0 && path != "/")
            {
                std::string path = req->getPath();
	            std::vector<std::string> pathVec = SplitOnChar(path, '/');

                std::vector<std::string>::iterator pathBegin = pathVec.begin();
                std::vector<std::string>::iterator pathEnd = pathVec.end();

            	// Route Path
            	return RouteRequestInSubroutes(req, resp, PATH, pathBegin, pathEnd);
            
            }
        }
        
        return ResolveRequest(req, resp);
    }

    if (NodeRouteSection == DOMAIN)
    {
        --nextSection;
    }
    else{
        ++nextSection;
    }
    
	return RouteRequestInSubroutes(req, resp, NodeRouteSection, nextSection, finalSection);
};



std::vector<std::string> RouteNode::SplitOnChar(const std::string& s, const char c) {
    std::vector<std::string> parts;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, c)) {
        if (!item.empty())
            parts.push_back(item);
    }
    return parts;
}

int RouteNode::ResolveRequest(const drogon::HttpRequestPtr& req, drogon::HttpResponsePtr& resp)
{
    resp->setContentTypeCode(drogon::CT_TEXT_HTML);
    resp->setBody("<html> Endpoint found at host: " + req->getHeader("Host") + "</html>");
    
    return 200;
};

int RouteNode::RouteRequestInSubroutes(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp,
    RouteSection currentRouteSection,
    std::vector<std::string>::iterator& nextSection,
    std::vector<std::string>::iterator& finalSection)
{
	for (RouteNode& subRoute : SubRoutes){
		int responseCode = subRoute.RouteRequest(req, resp, currentRouteSection, nextSection, finalSection);
		if (responseCode != 0) {
			return responseCode;
		}
	}

    return 404;
};

void RouteNode::ThrowFormatError(const int errorCode, const std::string ErrorMessage)
{
    throw std::make_pair(errorCode, ErrorMessage);
};