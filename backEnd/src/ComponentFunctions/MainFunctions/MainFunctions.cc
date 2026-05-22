#include "MainFunctions.h"

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
    std::shared_ptr<drogon::HttpResponse> resp,
    drogon::ContentType& desiredResponseType,
    int errorCode,
    const std::string& errorMessage)
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