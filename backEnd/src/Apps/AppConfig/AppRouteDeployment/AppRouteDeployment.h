#ifndef appRouteDeployment
#define appRouteDeployment

#include "../../../ComponentClasses/JsonDeserializedObject/JsonDeserializedObject.h"

class AppRouteDeployment : public JsonDeserializedObject
{
    public: 
        AppRouteDeployment() {};

        int GetAppNodeId();

        std::string GetRoute();

        std::string GetDomain();

        std::string GetPath();
        
    private:

        // Id of the particular AppNode in the AppTemplate
        int AppNodeId;

        std::string AppRoute;

        /*

        void ParseAppNodeId(const Json::Value&);
        void ParseAppRoute(const Json::Value&);

        void CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath);

        */
};


#endif