#include <optional>
#include <vector>
#include <fstream>

#include "AppManager.h"

AppManager::AppManager(){};

void AppManager::RegisterApp(std::string appName)
{
    // Register appfile as an AppTemplate 


    // FOR NOW: just extract the appJson:
    Json::Value AppJson = ReadAppJson(appName);

    RegisteredApps.push_back(AppTemplate(AppJson));
}

// For now just get the first  app
AppTemplate& AppManager::FindApp(std::string _appName, std::optional<AppVersion*> _appVersion)
{
    if (!_appVersion.has_value())
    {
        return FindAppTemplateLatest(_appName);
    }

    FindAppTemplateByVersion(_appName, _appVersion.value());
};

AppTemplate& AppManager::FindAppTemplateByVersion(std::string _appName, AppVersion* VersionPtr)
{
    AppVersion& TargetVerson = *VersionPtr;

    for(AppTemplate& _appTemplate : RegisteredApps)
    {
        if (_appTemplate.GetName() == _appName && TargetVerson == _appTemplate.GetVersion())
        {
            return _appTemplate;
        }
    }

    throw "App not found";
};

AppTemplate& AppManager::FindAppTemplateLatest(std::string _appName)
{
    AppTemplate* LatestAppTemplate;

    for(AppTemplate& _appTemplate : RegisteredApps)
    {
        if (_appTemplate.GetName() == _appName && _appTemplate.GetVersion() > LatestAppTemplate->GetVersion())
        {
            LatestAppTemplate = &_appTemplate;
        }
    }
    
    if (LatestAppTemplate == nullptr)
    {
        throw "App not found";
    }

    return *LatestAppTemplate;
};

void AppManager::DeployApp(std::string appName) {
    
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

