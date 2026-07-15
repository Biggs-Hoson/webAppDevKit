#include "AppDeploymentManager.h"

AppDeploymentManager::AppDeploymentManager()
{
    AppDeploymentManagerPtr = this;

    // Exceedingly temporary constructor of the appropriate appDeploymentConfig
    Json::Value appDeployment1;

    appDeployment1["appNodeId"] = 0;
    appDeployment1["appRoute"] = "0.0.0.0/notes";

    Json::Value appDeployments;
    appDeployments[0] = appDeployment1;

    Json::Value notesConfig;
    notesConfig["appId"] = 0;
    notesConfig["appName"] = "games";
    notesConfig["appVersion"] = "1.2.3";
    notesConfig["appHash"] = "abxyz";
    notesConfig["appAppRouteDeployments"] = appDeployments;

    ConfiguredApps.push_back(AppConfig(notesConfig));
    
};

void AppDeploymentManager::DeployApp(AppId& _appId)
{
    AppConfig& appCfg = FindAppConfigById(_appId);

    std::string AppName = appCfg.GetAppName();

    // Get AppTemplate
    AppTemplate appTempate = AppLibraryManagerPtr->FindApp(AppName);

    // Deploy database Objects
    

    // Deploy App Addresses
    DeployAppAddresses(appCfg, appTempate);
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

void AppDeploymentManager::DeployAppAddresses(AppConfig& _appConfig, AppTemplate& _appTemplate)
{
    for (AppRouteDeployment& appRouteConfig : _appConfig.GetAppRouteDeployments())
    {
        AppNodeTemplate& appRoute = _appTemplate.GetAppNodeById(appRouteConfig.GetAppNodeId());

        AddressTreeManagerPtr->DeployAppRoute(appRouteConfig, appRoute);
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