#include <vector>
#include <fstream>

#include "AppManager.h"

AppManager::AppManager(ServerManager& _serverManager)
    : ServerManagerObj(_serverManager){};

void AppManager::RegisterApp(std::string appName)
{
    // Register appfile as an AppTemplate 


    // FOR NOW: just extract the appJson:
    Json::Value AppJson = ReadAppJson(appName);

    RegisteredApps.push_back(AppTemplate(AppJson));
}

void AppManager::DeployApp(std::string appName) {


    //Deploy frontend

    // FOR NOW: don't bother about selecting registered apps:
    AppTemplate* appToDeploy = &RegisteredApps[0];

    // Deploy RouteMap

    // FOR NOW: deploy to the default domain:
    
    //ServerManagerObj.DeployAppRouteNode();
    
};



void AppManager::ActivateApp() 
{
    
};


Json::Value AppManager::ReadAppJson(std::string& appName)
{
    std::ifstream appJsonFile("./apps/" + appName + "/" + appName +".json");

    if (!appJsonFile.is_open()) {
        throw std::make_pair(500, "Could not open "+ appName + ".json");
    }

    Json::Value appJson;
    appJsonFile >> appJson;

    appJsonFile.close();

    return appJson;
}

