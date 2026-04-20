#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <drogon/drogon.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>


#include "./Routing/RouteNode/RouteNode.h"
#include "./AppManager/AppManager.h"


std::vector<RouteNode> DomainNodes;
Json::Value RouteMapJson;   

std::string HtmlErrorPage(const std::string& message){
	return "<html>" + message + "</html>";
};


std::vector<std::string> SplitDomain(const std::string& host) {
    std::vector<std::string> parts;
    std::stringstream ss(host);
    std::string item;

    while (std::getline(ss, item, '.')) {
        if (!item.empty())
            parts.push_back(item);
    }
    return parts;
}

void RouteRequest(const drogon::HttpRequestPtr& req, drogon::HttpResponsePtr& resp) {

	std::string host = req->getHeader("Host");

    std::vector<std::string> HostVec = SplitDomain(host);

    std::vector<std::string>::iterator nextSection = HostVec.end();
    std::vector<std::string>::iterator finalSection = HostVec.begin();


	for (RouteNode& DomainNode: DomainNodes)
    {
        int responseCode = DomainNode.RouteRequest(req, resp, DOMAIN, nextSection, finalSection);

        if (responseCode != 0) {
            return;
        }
    }

    // Top Level 404 error, other 404 errors should be handled in the DomainNode with either a raise or return based on the app's route design.
    throw std::make_pair(404, "Domain could not be found");
};

void HandleErrorResponse(std::shared_ptr<drogon::HttpResponse> resp, drogon::ContentType& desiredResponseType, int errorCode, const std::string& errorMessage)
{
    resp->setStatusCode(static_cast<drogon::HttpStatusCode>(errorCode));

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
};

std::string GetDefaultErrorMessage(int errorCode) {
	switch(errorCode)
    {
		case 404:
			return "Resource not found.";
		case 500:
            return "Something went wrong with the server. The specific problem could not be identified.";
		default:
			return "Something went wrong with your request. The problem could not be identified.";
	}
};


void commonHandler(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback
)
{
    // Create HTTP response
    drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();

    drogon::ContentType desiredResponseType = drogon::CT_TEXT_HTML; // Detect response type in future

    try
    {
        if (false)
        {
            throw std::pair(503, "Server routing is not functioning currently.");
        }
        if (DomainNodes.size() == 0)
        {
            throw std::pair(503, "Server has no domains set up for routing.");
        }
        
        RouteRequest(req, resp);
    }
    catch (int& errorCode)
    {
        std::string defaultErrorMessage = GetDefaultErrorMessage(errorCode);

        HandleErrorResponse(resp, desiredResponseType, errorCode, defaultErrorMessage);
    }
    catch (const std::pair<int, const std::string>& errorCodeMessage)
    {
        HandleErrorResponse(resp, desiredResponseType, errorCodeMessage.first, errorCodeMessage.second);
    }
    catch (const std::pair<int, const char*>& errorCodeMessage)
    {
        std::string errorMessage = std::string(errorCodeMessage.second);
        HandleErrorResponse(resp, desiredResponseType, errorCodeMessage.first, errorMessage);
    }
    catch (const std::exception& e) // Can add specific types of errors here if they correspond to specific HTML Codes.
    {
        std::string exceptionMessage = std::string(e.what());
        HandleErrorResponse(resp, desiredResponseType, 500, exceptionMessage);
    }
    catch (...) 
    {
        std::string exceptionMessage = GetDefaultErrorMessage(500);
        HandleErrorResponse(resp, desiredResponseType, 500, exceptionMessage);
    }

    callback(resp);
};

int main() {
    
    AppManager serverAppManager(DomainNodes);

    serverAppManager.GetDomainsFromConfig();

    serverAppManager.DeployApp("myNotes");

    drogon::app().loadConfigFile("./config.json");
    drogon::app().registerHandlerViaRegex(".*", &commonHandler);
    drogon::app().run();

    return 0;
}



/*
    Response types:
    newHttpJsonResponse(json);
    newHttpResponse()
    newFileResponse("./views/index.html");
*/

/*
    Request Methods:
    getMethod()
    getParameter(const std::string &key)
    getPath()
    getBody() or getJsonObject()
    getHeader("Host")

    getCookies()
    cookies()

    

    
*/

/* Respond with request aspects

void requestJsonMirrorHandler(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback
)
{
    std::string path = req->getPath();
    std::string host = req->getHeader("Host");

    Json::Value headers;

    for (const std::pair<const std::string, const std::string> &header : req->headers()) {
        headers[header.first] = header.second;
    }

    Json::Value json;
    json["path"] = req->path();
    json["host"] = host;
    json["method"] = req->methodString();
    json["headers"] = headers;

    auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
    
    callback(resp);
};



curl -X GET http://192.168.1.252 -H "Origin: http://williamlewin.dev"


*/