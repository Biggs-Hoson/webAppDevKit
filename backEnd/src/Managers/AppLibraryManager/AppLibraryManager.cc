#include <exception>
#include <optional>
#include <vector>
#include <fstream>

#include "AppLibraryManager.h"

AppLibraryManager::AppLibraryManager()
{
    AppLibraryManagerPtr = this;

    RegisterApp("myNotes");
};

void AppLibraryManager::RegisterApp(std::string appName)
{
    // Register appfile as an AppTemplate in the AppLibrary

    // FOR NOW: just extract the appJson and create the AppTemplate
    std::ifstream appJsonFile("./apps/" + appName + "/" + appName +".json");

    if (!appJsonFile.is_open()) {
        throw std::make_pair(500, "Could not open "+ appName + ".json");
    }

    Json::Value appJson;
    appJsonFile >> appJson;

    appJsonFile.close();

    AppLibrary.push_back(AppTemplate(appJson));
}


AppTemplate AppLibraryManager::FindApp(std::string _appName, std::optional<AppVersion*> _appVersion)
{
    try 
    {
        if (!_appVersion.has_value())
    {
        return FindAppTemplateLatest(_appName);
    }
    
    return FindAppTemplateByVersion(_appName, _appVersion.value());
    }
    catch (std::exception e)
    {
        // Check for correct app in appfolder,

        // FOR NOW:
        //RegisterApp("myNotes");
    }

    return FindAppTemplateLatest(_appName);
};

AppTemplate AppLibraryManager::FindAppTemplateByVersion(std::string _appName, AppVersion* VersionPtr)
{
    AppVersion TargetVerson = *VersionPtr;

    for(AppTemplate _appTemplate : AppLibrary)
    {
        if (_appTemplate.GetName() == _appName && TargetVerson == _appTemplate.GetVersion())
        {
            return _appTemplate;
        }
    }

    throw "App not found";
};

AppTemplate AppLibraryManager::FindAppTemplateLatest(std::string _appName)
{
    AppTemplate* LatestAppTemplate = nullptr;

    for(AppTemplate& _appTemplate : AppLibrary)
    {
        if (_appTemplate.GetName() == _appName)
        {
            if (LatestAppTemplate == nullptr)
            {
                LatestAppTemplate = &_appTemplate;
            }
            else 
            {
                AppVersion currentVersion = LatestAppTemplate->GetVersion();

                if(_appTemplate.GetVersion() > currentVersion)
                {
                    LatestAppTemplate = &_appTemplate;
                }
            }
            
        }
    }
    
    if (LatestAppTemplate == nullptr)
    {
        throw "App not found";
    }

    return *LatestAppTemplate;
};