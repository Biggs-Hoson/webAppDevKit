#ifndef appConfig
#define appConfig

#include <string>
#include <vector>


#include "../../ComponentClasses/JsonDeserializedObject/JsonDeserializedObject.h"
#include "AppRouteDeployment/AppRouteDeployment.h"
#include "../../ServerInfrastructure/Routing/AddressNode/AddressNode.h"
#include "../AppComponents/AppVersion/AppVersion.h"
#include "../AppComponents/AppId/AppId.h"

class AppConfig : public JsonDeserializedObject
{
    public: 
    
        AppConfig(const Json::Value&) {};

        AppId GetConfigId();

        std::string GetAppName();

        std::string GetAppHash();

        std::vector<AppRouteDeployment>& GetAppRouteDeployments();

    private:
        AppId AppConfigId;

        std::string AppName;

        AppVersion CorrespondingAppVersion;

        std::string AppHash;

        std::vector<AppRouteDeployment> AppRouteDeployments;

    /*

        void ParseAppId(const Json::Value&);
        AppId AppConfigId;

        void ParseAppName(const Json::Value&);
        std::string AppName;

        void ParseAppVersion(const Json::Value&);
        AppVersion CorrespondingAppVersion;

        void ParseAppHash(const Json::Value&);
        std::string AppHash;

        void ParseAppAppRouteDeployments(const Json::Value&);
        std::vector<AppRouteDeployment> AppRouteDeployments;
        */
    };



#endif