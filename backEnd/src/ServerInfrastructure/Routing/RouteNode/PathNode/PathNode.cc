#include "PathNode.h"

int PathNode::ResolveRequest(
	const drogon::HttpRequestPtr& req,
	drogon::HttpResponsePtr& resp
)
{
	resp->setContentTypeCode(drogon::CT_TEXT_HTML);
    resp->setBody("<html> Endpoint found at host: " + req->getHeader("Host") + "</html>");

    resp->setBody("<html> Hello Mum! </html>");
    
    return 200;
};