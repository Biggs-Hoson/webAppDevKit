#ifndef routeDeployment
#define routeDeployment

#include "../../../ComponentClasses/JsonToClass/JsonToClass.h"

class RouteDeployment : public JsonToClass
{
    public: 
        RouteDeployment(const Json::Value& routeDeploymentJson);

        int GetAppNodeId();

        int GetRouteStartId();

        std::vector<std::string>& GetSubdomainRoute();

        std::vector<std::string>& GetPathRoute();
        

    private:

        // Id of the particular AppNode in the AppTemplate
        int AppNodeId;
        void ParseAppNodeId(const Json::Value&);

        int RouteStartId;
        void ParseRouteStartId(const Json::Value&);

        std::vector<std::string> SubdomainRoute;
        void ParseSubdomainRoute(const Json::Value&);

        std::vector<std::string> PathRoute;
        void ParsePathRoute(const Json::Value&);

        void CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath);
};


#endif