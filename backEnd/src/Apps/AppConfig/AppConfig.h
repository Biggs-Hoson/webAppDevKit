#ifndef appConfig
#define appConfig

#include "../../JsonToTemplate/JsonToTemplate.h"
#include "RouteDeployment/RouteDeployment.h"
#include "../../Routing/RouteNode/RouteNode.h"
#include "../AppManager/AppManager.h"
#include "../AppTemplate/AppVersion/AppVersion.h"
#include <vector>

class AppConfig : public JsonToTemplate
{
        public: 
        AppConfig(const Json::Value&);

        void GetAppTemplate(AppManager&);

        void DeployApp(std::vector<RouteNode>&);

	private:

        void ParseAppId(const Json::Value&);
        int AppId;

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