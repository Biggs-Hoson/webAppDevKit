#include "AppTemplate.h"
#include "AppNodeTemplate/AppNodeTemplate.h"
#include "../AppComponents/AppVersion/AppVersion.h"
#include "json/value.h"

#include <string>
#include <vector>


AppTemplate::AppTemplate(Json::Value& _appJson)
{
    RegisterStringField("appName", &AppName);

    RegisterStringField("appVersion", &Version);

    RegisterObjectField("databaseObjects", &dboTemplate);

    RegisterObjectArrayElement("routeMap", &AppAddressNodes);
    
    DeserializedJson(_appJson, &DeserializationErrors);
};

AppNodeTemplate& AppTemplate::GetAppNodeById(int appId)
{
    return AppAddressNodes[appId];
}

std::string AppTemplate::GetHash()
{
    return "abxyz";
}

std::string AppTemplate::GetName()
{
    return AppName;
}

AppVersion& AppTemplate::GetVersion()
{
    return Version;
}

