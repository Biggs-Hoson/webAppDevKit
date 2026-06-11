#include "RouteNode.h"
#include <cstddef>
#include <memory>

RouteNode::RouteNode(RouteNodeTemplate& _nodeTemplate)
{
    // Set Match Critera
    MatchCriteraPtr = MatchCriteria::GetMatchCriteraPtr(_nodeTemplate.GetMatchCritera());

    StructureFromTemplate(_nodeTemplate);
}

// Used so can create with an AppNodeTemplate, that doesn't have a match string
void RouteNode::StructureFromTemplate(RouteNodeTemplate& _nodeTemplate)
{
    // Set Endpoint
    // Endpoint = ...

    // Create subroutes
    for(RouteNodeTemplate& subRoute : _nodeTemplate.GetSubRoutes())
    {
        CreateSubRoute(subRoute);
    }
}

int RouteNode::RouteRequest(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp, 
    RequestedRoute* route
)
{
    // Match Request

    if (!MatchRequest(route)){
    	// Match Unsuccessful, return 0 to attempt next RouteNode
        return 0;
    }

    if (route->RoutingComplete())
    {
        return ResolveRequest(req, resp);
    }

    return RouteRequestInSubroutes(req, resp, route);
}

bool RouteNode::MatchRequest(
    RequestedRoute* _route
)
{
    return _route->MatchRequest(MatchCriteraPtr.get());
};

bool RouteNode::RouteRequestInSubroutes(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp,
    RequestedRoute* _route
)
{
    for (std::unique_ptr<RouteNode>& subRoutePtr : SubRoutes){
		int responseCode = subRoutePtr->RouteRequest(req, resp, _route);
		if (responseCode != 0) {
			return responseCode;
		}
	}

    return 404;
};

void RouteNode::CreateSubRoute(RouteNodeTemplate _subNodeTemplate)
{
    SubRoutes.push_back(std::make_unique<RouteNode>(_subNodeTemplate));
};

int RouteNode::ResolveRequest(
	const drogon::HttpRequestPtr& req,
	drogon::HttpResponsePtr& resp
)
{
	resp->setContentTypeCode(drogon::CT_TEXT_HTML);
    resp->setBody("<html> Endpoint found at host: " + req->getHeader("Host") + "</html>");

    resp->setBody("<html> Hello Mum! </html>");
    
    return 200;
};

RouteNode* RouteNode::GetRouteNodeInSubRoutes(RouteNodeAddress& _address, bool createMode)
{
    for(std::unique_ptr<RouteNode>& nodePtr : SubRoutes)
    {
        RouteNode* addressNodePtr = nodePtr->GetRouteNode(_address, createMode);

        if (addressNodePtr != std::nullptr_t())
        {
            return addressNodePtr;
        }
    }

    if (createMode)
    {
        //CreateRemainingAddress(_address);
    }
    
    return std::nullptr_t();
}

RouteNode* RouteNode::GetRouteNode(RouteNodeAddress& _address, bool createMode)
{
    if(!_address.MatchRequest(MatchCriteraPtr.get()))
    {
        return nullptr;
    }

    if(_address.RoutingComplete())
    {
        return AddressFound(_address, createMode);
    }

    return GetRouteNodeInSubRoutes(_address, createMode);

    
};

RouteNode* RouteNode::AddressFound(RouteNodeAddress&, bool)
{
    return this;
}