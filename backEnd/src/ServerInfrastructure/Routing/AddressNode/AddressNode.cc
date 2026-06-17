#include "AddressNode.h"


// ---------- Constructor Functions ---------- //

AddressNode::AddressNode(AddressNodeTemplate& _nodeTemplate)
{
    // Set Match Critera
    MatchCriteraPtr = MatchCriteria::GetMatchCriteraPtr(_nodeTemplate.GetMatchCritera());

    StructureFromTemplate(_nodeTemplate);
}

// Used so can create with an AppNodeTemplate, that doesn't have a match string
void AddressNode::StructureFromTemplate(AddressNodeTemplate& _nodeTemplate)
{
    // Set Endpoint
    // Endpoint = ...

    // Create subroutes
    for(AddressNodeTemplate& subRoute : _nodeTemplate.GetSubRoutes())
    {
        CreateSubRoute(subRoute);
    }
}



// ---------- Routing Functions ---------- //

int AddressNode::RouteRequest(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp, 
    RequestedRoute* route
)
{
    // Match Request

    if (!MatchRequest(route)){
    	// Match Unsuccessful, return 0 to attempt next AddressNode
        return 0;
    }

    if (route->RoutingComplete())
    {
        return ResolveRequest(req, resp);
    }

    return RouteRequestInSubroutes(req, resp, route);
}

bool AddressNode::MatchRequest(
    RequestedRoute* _route
)
{
    return _route->MatchRequest(MatchCriteraPtr.get());
};

bool AddressNode::RouteRequestInSubroutes(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp,
    RequestedRoute* _route
)
{
    for (std::unique_ptr<AddressNode>& subRoutePtr : SubRoutes){
		int responseCode = subRoutePtr->RouteRequest(req, resp, _route);
		if (responseCode != 0) {
			return responseCode;
		}
	}

    return 404;
};

// ---------- Routing Functions ---------- //

void AddressNode::CreateSubRoute(AddressNodeTemplate _subNodeTemplate)
{
    SubRoutes.push_back(std::make_unique<AddressNode>(_subNodeTemplate));
};

int AddressNode::ResolveRequest(
	const drogon::HttpRequestPtr& req,
	drogon::HttpResponsePtr& resp
)
{
	resp->setContentTypeCode(drogon::CT_TEXT_HTML);
    resp->setBody("<html> Endpoint found at host: " + req->getHeader("Host") + "</html>");

    resp->setBody("<html> Hello Mum! </html>");
    
    return 200;
};

AddressNode* AddressNode::GetAddressNodeInSubRoutes(AddressNodeAddress& _address, bool createMode)
{
    for(std::unique_ptr<AddressNode>& nodePtr : SubRoutes)
    {
        AddressNode* addressNodePtr = nodePtr->GetAddressNode(_address, createMode);

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

AddressNode* AddressNode::GetAddressNode(AddressNodeAddress& _address, bool createMode)
{
    if(!_address.MatchRequest(MatchCriteraPtr.get()))
    {
        return nullptr;
    }

    if(_address.RoutingComplete())
    {
        return AddressFound(_address, createMode);
    }

    return GetAddressNodeInSubRoutes(_address, createMode);

    
};

AddressNode* AddressNode::AddressFound(AddressNodeAddress&, bool)
{
    return this;
}