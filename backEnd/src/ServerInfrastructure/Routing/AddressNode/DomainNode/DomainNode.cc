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

        return RoutePath(req, resp, &pathRequest);
    }
    
    return HitEndpoint(req, resp);
};

int DomainNode::RoutePath(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp, 
    RequestedRoute* _route
)
{
    for (AddressNode& subPath : PathNodes){
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


void DomainNode::CreateSubRoute(AddressNodeTemplate _subNodeTemplate)
{
    PathNodes.push_back(AddressNode(_subNodeTemplate));
};

AddressNode* DomainNode::AddressFound(AddressNodeAddress& _address, bool createMode)
{
    _address.SetDomainMatch(false);

    if(_address.RoutingComplete())
    {
        return this;
    }

    for(AddressNode& pathNodePtr : PathNodes)
    {
        AddressNode* addressNodePtr = pathNodePtr.GetAddressNode(_address, createMode);

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