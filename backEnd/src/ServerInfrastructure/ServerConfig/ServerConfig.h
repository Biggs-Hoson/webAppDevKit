#ifndef serverConfig
#define serverConfig

#include "../../ComponentClasses/JsonDeserializedObject/JsonDeserializedObject.h"

class ServerConfig : public JsonDeserializedObject
{
    public:
        ServerConfig(std::string = "./config.json");

    private:
        void GetServerConfig(std::string = "./config.json");

        std::vector<std::string> RootDomains;
};

#endif