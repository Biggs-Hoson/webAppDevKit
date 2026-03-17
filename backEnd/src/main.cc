#include <drogon/drogon.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>

#include "./routing/RouteNode.h"



// dedicated hosts, all others to the main PathNode


void commonHandler(
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
    //drogon::HttpResponse::newFileResponse("./views/index.html");
    callback(resp);
    

    //resp->setStatusCode(drogon::k200OK);
    //resp->setContentTypeCode(drogon::CT_TEXT_HTML);
    //resp->setBody(path + " " + host);

    //callback(resp);
}



int main() {
    drogon::app().loadConfigFile("./config.json");
    drogon::app().registerHandler("/{path:.*}", &commonHandler);
    drogon::app().run();
    return 0;
}

/*
    Json::Value headers;

    for (const std::pair<const std::string, const std::string> &header : req->headers()) {
        headers[header.first] = header.second;
    }

    Json::Value json;
    json["path"] = req->path();
    json["method"] = req->methodString();
    json["headers"] = headers;

*/

/*
    Response types:
    newHttpJsonResponse(json);
    newHttpResponse()
*/

/*
    Request Methods
    getMethod()
    getParameter(const std::string &key)
    getPath()
    getBody() or getJsonObject()
    getHeader("Host")

    getCookies()
    cookies()

    
*/