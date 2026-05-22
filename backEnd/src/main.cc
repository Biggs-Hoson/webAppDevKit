#include "./Managers/ServerManager/ServerManager.h"
#include "./ComponentFunctions/MainFunctions/MainFunctions.h"
#include "./ServerInfrastructure/Routing/RouteNode/RouteTree/RouteTree.h"

RouteTree ServerRouteTree;

int main() {
    ServerManager ServerManagerObj(ServerRouteTree);

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
        ServerRouteTree.RouteRequest(req, resp);
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