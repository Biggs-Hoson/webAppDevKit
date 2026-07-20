#ifndef serverConfig
#define serverConfig

#include "../../ComponentClasses/JsonDeserializedObject/JsonDeserializedObject.h"

class ServerConfig : public JsonDeserializedObject
{
    /*
    public:
        ServerConfig(std::string = "./config.json");

    private:
        void GetServerConfig(std::string = "./config.json");

        void ParseRootDomains(const Json::Value&);
        std::vector<std::string> RootDomains;
        
        void CollectChildErrors(std::vector<std::string>& jsonErrors, std::string currentPath);

        */
};

#endif