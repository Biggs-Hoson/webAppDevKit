#ifndef appNodeTemplate
#define appNodeTemplate

#include <string>
#include <vector>

#include <drogon/drogon.h>
#include "../AddressNodeTemplate/AddressNodeTemplate.h"


class AppNodeTemplate : public AddressNodeTemplate
{
    public:
        AppNodeTemplate();

        std::string GetDefaultDeployment();

    private:
        std::string defaultDeployment;
};

#endif