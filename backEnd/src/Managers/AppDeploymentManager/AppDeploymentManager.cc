#include "AppDeploymentManager.h"

AppDeploymentManager::AppDeploymentManager()
{
    Json::Value appDeployment1;

    appDeployment1["appNodeId"] = 0;
    appDeployment1["appRoute"] = "*/notes";

    Json::Value appDeployments;
    appDeployments[0] = appDeployment1;

    Json::Value notesConfig;
    notesConfig["appId"] = 0;
    notesConfig["appName"] = "myNotes";
    notesConfig["appVersion"] = "1.2.3";
    notesConfig["appHash"] = "abxyz";
    notesConfig["appRouteDeployments"] = appDeployments;

    ConfiguredApps.push_back(AppConfig(notesConfig));
    
};

void AppDeploymentManager::DeployApp(AppId& _appId, AppLibraryManager& _appLibraryManager, AddressTreeManager& _AddressTreeManager)
{
    AppConfig& appCfg = FindAppConfigById(_appId);

    std::string AppName = appCfg.GetAppName();

    // Get AppTemplate
    AppTemplate appTempate = _appLibraryManager.FindApp(AppName);

    // Deploy App AddressTree
    DeployAppAddressTree(appCfg, appTempate, _AddressTreeManager);
};

AppConfig& AppDeploymentManager::FindAppConfigById(AppId& _appId)
{
    for(AppConfig& config : ConfiguredApps)
    {
        if (config.GetConfigId() == _appId)
        {
            return config;
        }
    }

    throw "App config not found by configId: " + _appId.GetIdString();
};

void AppDeploymentManager::DeployAppAddressTree(AppConfig& _appConfig, AppTemplate& _appTemplate, AddressTreeManager& _AddressTreeManager)
{
    for (RouteDeployment& appRouteConfig : _appConfig.GetRouteDeployments())
    {
        AppNodeTemplate& appRoute = _appTemplate.GetAppNodeById(appRouteConfig.GetAppNodeId());

        _AddressTreeManager.DeployAppRoute(appRouteConfig, appRoute);
    }
};

std::vector<AppId> AppDeploymentManager::GetIdsList()
{
    std::vector<AppId> AppIds;

    for (AppConfig& config : ConfiguredApps )
    {
        AppIds.push_back(config.GetConfigId());
    }

    return AppIds;
};