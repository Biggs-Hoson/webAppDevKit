#ifndef routeDeployment
#define routeDeployment

#include "../../../JsonToTemplate/JsonToTemplate.h"

class RouteDeployment : public JsonToTemplate
{
	public: 
    	RouteDeployment(const Json::Value& routeDeploymentJson);

        

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