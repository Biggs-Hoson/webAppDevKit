#include "./HttpRoutingContext.h"

HttpRoutingContext::HttpRoutingContext(
    const drogon::HttpRequestPtr& req,
    ResponseCallback callback,
    AddressNodeChildren* initialTree
) : RoutingContext(req->getHeader("Host"), req->getPath(), initialTree),
    RequestPtr(req),
    CallbackFunction(callback),
    ServerAddressTree(initialTree)
{
    if (ServerAddressTree == nullptr)
    {
        HandleErrorResponse(503, "Server has no AddressTree set.");
        return;
    }
    else if (ServerAddressTree->Empty())
    {
        HandleErrorResponse(503, "Server has no routes in current tree.");
        return;
    }
    try
    {
        // Handle Cookies here.


	    // Handle Path only top level node:
        if (RoutingComplete())
        {
            AddressNode* topNode = dynamic_cast<AddressNode*>(initialTree);

            if(topNode != nullptr)
            {
                ResolveWithCurrentNode(topNode);
            }
            else {
                HandleErrorResponse(404, "Server has no top level resource");
            }

            return;
        }

        ServerAddressTree->RouteRequestInChildren(this);
    }
    catch (const std::pair<int, const std::string>& errorCodeMessage)
    {
        HandleErrorResponse(errorCodeMessage.first, errorCodeMessage.second);
    }
    catch (const std::pair<int, const char*>& errorCodeMessage)
    {
        HandleErrorResponse(errorCodeMessage.first, errorCodeMessage.second);
    }
    catch (const std::exception& e) // Can add specific types of errors here if they correspond to specific HTML Codes.
    {
        HandleErrorResponse(500, e.what());
    }
    catch (int& errorCode)
    {
        HandleErrorResponse(errorCode);
    }
    catch (...) 
    {
        HandleErrorResponse();
    }
};

void HttpRoutingContext::UpdateRoutingContext(AddressNode* _node)
{
    if(_node->GetErrorResolver() != nullptr)
    {
        ErrorResolverPtr = _node->GetErrorResolver();
    }
};

bool HttpRoutingContext::ResolveWithCurrentNode(AddressNode* _node)
{
    if(_node == nullptr)
    {
        HandleErrorResponse(404);

        return true;
    }

    EndpointMap* mapPtr = _node->GetEndpointMap();

    if (mapPtr == nullptr)
    {   
        HandleErrorResponse(404, "Current URL has no handler");

        return true;
    }

    EndpointResolver* resolver = mapPtr->GetEndpoint(RequestPtr->getMethod());
    
    if (resolver == nullptr)
    {
        HandleErrorResponse(405);

        return true;
    }

    drogon::HttpResponsePtr resp = resolver->Resolve(this);

    CallbackFunction(resp);

    return true;
};

void HttpRoutingContext::HandleNotFound() // Not found while routing
{
    if (RoutingInPath()) // May want to give more descriptive location errors later
    {
        if(CurrentSegment == PathSplit.begin())
        {
            HttpResponseMessage = "First Path Segment could not be found";
        }

        HttpResponseMessage = "Path could not be found";
    }
    else {
        if (CurrentSegment == --DomainSplit.end() || ++CurrentSegment == --DomainSplit.end())
        {
            HttpResponseMessage = "Domain could not be found";
        }

        HttpResponseMessage = "Subdomain could not be found";
    }

    HandleErrorResponse(404);
};

bool HttpRoutingContext::HandleErrorResponse()
{
    drogon::HttpResponsePtr resp;

    // From context, determine the appropriate level of detail / error response
    if(ErrorResolverPtr != nullptr)
    {
        resp = ErrorResolverPtr->Resolve(this);
    }
    else {
        resp = drogon::HttpResponse::newHttpResponse();
    
        drogon::ContentType desiredResponseType = drogon::CT_TEXT_HTML; // Detect response type in future

        resp->setStatusCode(static_cast<drogon::HttpStatusCode>(HttpCode));

        if (HttpResponseMessage == "")
        {
            HttpResponseMessage = GetDefaultErrorMessage();
        }

        switch(desiredResponseType)
        {
            case drogon::CT_TEXT_HTML:
                resp->setContentTypeCode(drogon::CT_TEXT_HTML);
                resp->setBody(HtmlErrorPage(HttpResponseMessage));
                break;

            case drogon::CT_APPLICATION_JSON:
            default:
                resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
                resp->setBody("\"Error Message\":\"" + HttpResponseMessage + "\"}");
                break;
        }
    }
    
    CallbackFunction(resp);

    return true;
};

bool HttpRoutingContext::HandleErrorResponse(int _code)
{
    HttpCode = _code;

    return HandleErrorResponse();
}

bool HttpRoutingContext::HandleErrorResponse(int _code, std::string _msg)
{
    HttpResponseMessage = _msg;

    return HandleErrorResponse(_code);   
}

std::string HttpRoutingContext::GetDefaultErrorMessage() {
	switch(HttpCode)
    {
		case 404:
			return "Resource not found.";
		case 405:
			return "Incorrect method.";
		case 500:
            return "Something went wrong with the server. The specific problem could not be identified.";
		default:
			return "Something went wrong with your request. The specific problem could not be identified.";
	}
};

std::string HttpRoutingContext::HtmlErrorPage(const std::string& message){
	return "<html>" + message + "</html>";
};