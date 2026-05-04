#ifndef appNodeTemplate
#define appNodeTemplate

#include <string>
#include <vector>

#include <drogon/drogon.h>
#include "../RouteNodeTemplate/RouteNodeTemplate.h"


class AppNodeTemplate : public RouteNodeTemplate
{
    public:
        AppNodeTemplate(const Json::Value&);

    private:
        std::string defaultDeployment;

        void ParseDefaultDeployment(const Json::Value&);
};

#endif