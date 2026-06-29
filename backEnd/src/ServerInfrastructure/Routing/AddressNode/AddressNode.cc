#include "AddressNode.h"


// ---------- Constructor and Setup Functions ---------- //

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
};

// ---------- Routing Function ---------- //

AddressNode::RouteRequest(RoutingContext* routeContext)
{
    std::optional<bool> routingState = routeContext->MatchNode(*this)

    // Match Request
    if (routingState.hasValue()){
    	
        // routingState.value ==
        // false:  Match Unsuccessful, return false to attempt next AddressNode
        // truee:  Routing Complete, return true to end Routing Request
        return routingState.value();
    }

    for (std::unique_ptr<AddressNode>& subRoutePtr : SubRoutes){
		if (subRoutePtr->RouteRequest(routeContext)) {
			return true;
		}
	}

    return true; // Routing Performed, no more actiosn to take
}


// ---------- Endpoint functions ---------- //

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


void AddressNode::CreateSubRoute(AddressNodeTemplate _subNodeTemplate)
{
    SubRoutes.push_back(std::make_unique<AddressNode>(_subNodeTemplate));
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