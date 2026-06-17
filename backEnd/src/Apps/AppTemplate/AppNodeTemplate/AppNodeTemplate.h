#ifndef appNodeTemplate
#define appNodeTemplate

#include <string>
#include <vector>

#include <drogon/drogon.h>
#include "../AddressNodeTemplate/AddressNodeTemplate.h"


class AppNodeTemplate : public AddressNodeTemplate
{
    public:
        AppNodeTemplate(const Json::Value&);

    private:
        std::string defaultDeployment;

        void ParseDefaultDeployment(const Json::Value&);
};

#endif