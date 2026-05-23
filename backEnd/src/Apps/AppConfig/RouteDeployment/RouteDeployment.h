#ifndef routeDeployment
#define routeDeployment

#include "../../../ComponentClasses/JsonToClass/JsonToClass.h"

class RouteDeployment : public JsonToClass
{
    public: 
        RouteDeployment(const Json::Value& routeDeploymentJson);

        int GetAppNodeId();

        std::string GetRoute();
        
    private:

        // Id of the particular AppNode in the AppTemplate
        int AppNodeId;
        void ParseAppNodeId(const Json::Value&);

        std::string AppRoute;
        void ParseAppRoute(const Json::Value&);

        void CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath);
};


#endif