#include "MainFunctions.h"
#include <optional>

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

std::string HtmlErrorPage(const std::string& message){
	return "<html>" + message + "</html>";
};

void HandleErrorResponse(
    const drogon::HttpRequestPtr& req,
    ResponseCallback callbackFunc,
    int errorCode = 500,
    const std::optional<std::string> errorMessage = std::nullopt)
{
    drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
    
    drogon::ContentType desiredResponseType = drogon::CT_TEXT_HTML; // Detect response type in future

    resp->setStatusCode(static_cast<drogon::HttpStatusCode>(errorCode));

    std::string msg = "";

    if (errorMessage == std::nullopt)
    {
        msg = GetDefaultErrorMessage(errorCode);
    }
    else {
        msg = errorMessage.value();
    }

    switch(desiredResponseType)
    {
        case drogon::CT_TEXT_HTML:
            resp->setContentTypeCode(drogon::CT_TEXT_HTML);
            resp->setBody(HtmlErrorPage(msg));
            break;

        case drogon::CT_APPLICATION_JSON:
        default:
            resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
            resp->setBody("\"Error Message\":\"" + msg + "\"}");
            break;
    }
    
    callbackFunc(resp);
};