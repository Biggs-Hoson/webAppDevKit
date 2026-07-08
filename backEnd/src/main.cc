#include "drogon/HttpTypes.h"


// Infrastructure
#include "./ServerInfrastructure/Routing/RoutingContext/HttpRoutingContext/HttpRoutingContext.h"
#include "./ServerInfrastructure/ServerContextProvider/ServerContextProvider.h"

// Managers
#include "./Managers/ServerCentralManager/ServerCentralManager.h"


int main() {
    // Main Variables
    AddressNodeChildren* AddressTreePtr = nullptr;

    ServerContextProvider ServerContext;

    // Managers 
    ServerCentralManager ServerManager(&ServerContext);
    AddressTreeManager ServerAddressTreeManager(&ServerContext);
    AppDeploymentManager ServerAppDeploymentManager(&ServerContext);
    AppLibraryManager ServerAppLibraryManager(&ServerContext);

    ServerManager.StartServer();

    AddressTreePtr = ServerAddressTreeManager.GetAddressTreePtr();
    
    drogon::app().registerHandlerViaRegex(
        ".*", 
        [AddressTreePtr](const drogon::HttpRequestPtr &request,
           std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            try {
            {
                HttpRoutingContext requestContext(request, callback, AddressTreePtr);
            }
            } catch (...) {
                drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
                resp->setBody("An unhandled error occured");
                resp->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
                callback(resp);
            }
        });

    drogon::app().run();

    return 0;
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

curl -X GET http://192.168.10.3 -H "Origin: http://williamlewin.dev"


*/

/* Note on valid domains:

Case insensitive letters
Digits
Hyphens (not at the start or end)
Dots as delimiters

café.com becomes xn--caf-dma.com
ASCII: xn-- version
*/

/* Note on valid paths:

Case sensitive letters
Digits
-._~

Reserved:
/
% for percent encoding
? query string delimiter
# fragment (may not be sent)
; Matrix parameters

Sanitization:
remove .. for paths (including %2e)
remove %00 (null bytes)
*/