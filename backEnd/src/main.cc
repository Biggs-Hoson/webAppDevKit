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

std::string HtmlErrorPage(const std::string& message){
	return "<html>" + message + "</html>";
};

void RouteRequest(const drogon::HttpRequestPtr& req, drogon::HttpResponsePtr& resp) {

	// std::string host = req->getHeader("Host");

    std::string path = req->getPath();

	for (RouteNode& DomainNode: DomainNodes)
    {
        int responseCode = DomainNode.RouteRequest(req, resp, PATH, path);

        if (responseCode != 0) {
            return;
        }
    }

    // Top Level 404 error, other 404 errors should be handled in the DomainNode with either a raise or return based on the app's route design.
    throw std::make_pair(404, "Domain could not be found");
};

void HandleErrorResponse(std::shared_ptr<drogon::HttpResponse> resp, drogon::ContentType& desiredResponseType, int errorCode, std::string& errorMessage)
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

Json::Value RouteMapJson;   

void commonHandler(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback
)
{
    std::cout << "Request recieved.";

    // Create HTTP response
    drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();

    drogon::ContentType desiredResponseType = drogon::CT_TEXT_HTML; // Detect response type in future

    try
    {
        if (true)
        {
            throw std::pair<int, std::string>(503, "Server routing is not functioning currently.");
        }
        if (DomainNodes.size() == 0)
        {
            throw std::pair<int, std::string>(503, "Server has no domains set up for routing.");
        }
        
        RouteRequest(req, resp);
    }
    catch (int& errorCode)
    {
        std::string defaultErrorMessage = GetDefaultErrorMessage(errorCode);

        HandleErrorResponse(resp, desiredResponseType, errorCode, defaultErrorMessage);
    }
    catch (std::pair<int, std::string>& errorCodeMessage)
    {
        HandleErrorResponse(resp, desiredResponseType, errorCodeMessage.first, errorCodeMessage.second);
    }
    catch (std::exception& e) // Can add specific types of errors here if they correspond to specific HTML Codes.
    {
        std::string exceptionMessage = e.what();
        HandleErrorResponse(resp, desiredResponseType, 500, exceptionMessage);
    }
    catch (...)
    {
        std::string exceptionMessage = GetDefaultErrorMessage(500);
        HandleErrorResponse(resp, desiredResponseType, 500, exceptionMessage);
    }

    callback(resp);
};




std::string RouteMapJsonStr= "[{\"path\": \"1\",\"subRoutes\": [{ \"path\": \"a\"},{ \"path\": \"b\"},{ \"path\": \"c\"}]},{\"path\": \"2\",\"subRoutes\": [{ \"path\": \"a\"},{ \"path\": \"b\"},{ \"path\": \"c\"}]}]";



int main() {

    // Construct Basic JSON route for now:
    Json::Reader reader;

    bool parsingSuccessful = reader.parse( RouteMapJsonStr.c_str(), RouteMapJson);
    if ( !parsingSuccessful )
    {
        std::cout << "Failed to parse"
            << reader.getFormattedErrorMessages();
        return 1;
    }

    std::cout << RouteMapJson.type();

    AppManager serverAppManager(DomainNodes);

    serverAppManager.DeployApp(RouteMapJson);

    //serverAppManager.ActivateApp();

    drogon::app().loadConfigFile("./config.json");
    drogon::app().registerHandler("/{path:.*}", &commonHandler);
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

*/