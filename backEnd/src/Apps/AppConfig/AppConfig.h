#ifndef appConfig
#define appConfig

#include <string>
#include <vector>


#include "../../ComponentClasses/JsonToClass/JsonToClass.h"
#include "RouteDeployment/RouteDeployment.h"
#include "../../ServerInfrastructure/Routing/RouteNode/RouteNode.h"
#include "../AppComponents/AppVersion/AppVersion.h"
#include "../AppComponents/AppId/AppId.h"

class AppConfig : public JsonToClass
{
    public: 
        AppConfig(const Json::Value&);

        AppId GetConfigId();

        std::string GetAppName();

        std::string GetAppHash();

        std::vector<RouteDeployment>& GetRouteDeployments();

    private:

        void ParseAppId(const Json::Value&);
        AppId AppConfigId;

        void ParseAppName(const Json::Value&);
        std::string AppName;

        void ParseAppVersion(const Json::Value&);
        AppVersion CorrespondingAppVersion;

        void ParseAppHash(const Json::Value&);
        std::string AppHash;

        void ParseAppRouteDeployments(const Json::Value&);
        std::vector<RouteDeployment> RouteDeployments;

        void CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath);
    };



#endif