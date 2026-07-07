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
    try
    {
        if (ServerAddressTree == nullptr)
        {
            throw std::pair(503, "Server has no AddressTree set.");
        }

        if (ServerAddressTree->Empty())
        {
            throw std::pair(503, "Server has no routes in current tree.");
        }

	    // Handle Path only top level node:
        if (RoutingComplete())
        {
            AddressNode* topNode = dynamic_cast<AddressNode*>(initialTree);

            if(topNode != nullptr)
            {
                ResolveWithCurrentNode(topNode);
            }
            else {
                throw std::pair(404, "Server has no top level resource");
            }
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

void HttpRoutingContext::HandleNotFound()
{
    // else handle with current error handler node

    std::cout << "Not Found" << std::endl;

    if (RoutingInPath()) // May want to give more descriptive location errors later
    {
        std::cout << "Path" << std::endl;

        if(CurrentSegment == PathSplit.begin())
        {
            std::cout << "Yeah" << std::endl;

            throw std::make_pair(404, "First Path Segment could not be found");
        }

        throw std::make_pair(404, "Path could not be found");
    }
    else {
        if (CurrentSegment == --DomainSplit.end() || ++CurrentSegment == --DomainSplit.end())
        {
            throw std::make_pair(404, "Domain could not be found");
        }

        throw std::make_pair(404, "Subdomain could not be found");
    }
};

bool HttpRoutingContext::ResolveWithCurrentNode(AddressNode* _node)
{
    drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();

    resp->setBody("Success");

    CallbackFunction(resp);

    return true;
};

void HttpRoutingContext::HandleErrorResponse(
    int errorCode,
    std::string errorMessage)
{
    drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
    
    drogon::ContentType desiredResponseType = drogon::CT_TEXT_HTML; // Detect response type in future

    resp->setStatusCode(static_cast<drogon::HttpStatusCode>(errorCode));

    if (errorMessage == "")
    {
        errorMessage = GetDefaultErrorMessage(errorCode);
    }

    switch(desiredResponseType)
    {
        case drogon::CT_TEXT_HTML:
            resp->setContentTypeCode(drogon::CT_TEXT_HTML);
            resp->setBody(HtmlErrorPage(errorMessage));
            break;

        case drogon::CT_APPLICATION_JSON:
        default:
            resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
            resp->setBody("\"Error Message\":\"" + errorMessage + "\"}");
            break;
    }
    
    CallbackFunction(resp);
};

std::string HttpRoutingContext::GetDefaultErrorMessage(int errorCode) {
	switch(errorCode)
    {
		case 404:
			return "Resource not found.";
		case 500:
            return "Something went wrong with the server. The specific problem could not be identified.";
		default:
			return "Something went wrong with your request. The specific problem could not be identified.";
	}
};

std::string HttpRoutingContext::HtmlErrorPage(const std::string& message){
	return "<html>" + message + "</html>";
};
