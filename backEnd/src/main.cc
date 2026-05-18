#include "./Managers/ServerManager/ServerManager.h"
#include "./ComponentFunctions/MainFunctions/MainFunctions.h"

std::vector<RouteNode> DomainNodes;

int main() {
    ServerManager ServerManagerObj(DomainNodes);

    ServerManagerObj.StartServer();

    drogon::app().registerHandlerViaRegex(".*", &commonHandler);
    drogon::app().run();

    return 0;
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

void RouteRequest(
    const drogon::HttpRequestPtr& req,
    drogon::HttpResponsePtr& resp) {

	std::string host = req->getHeader("Host");

    std::vector<std::string> HostVec = SplitDomain(host);

    std::vector<std::string>::iterator nextSection = HostVec.end();
    std::vector<std::string>::iterator finalSection = HostVec.begin();

    std::string hostSplit = "";

    for (const std::string str : HostVec)
    {
        hostSplit.append(str + ", ");
    }

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