#include "AppDeploymentManager.h"

AppDeploymentManager::AppDeploymentManager()
{
    //Temp:
    std::string s = "{\n\"appId\": 0,\n\"appName\": \"myNotes\",\n\"appVersion\": \"1.2.3\",\n\"appHash\": \"abxyz\",\n\"appRouteDeployments\": [\n{\n\"appNodeId\": 0,\n\"appRoute\": \"*/notes\"\n}\n]\n}";

    Json::Value notesConfig(s);

    ConfiguredApps.push_back(AppConfig(notesConfig));
};

void AppDeploymentManager::DeployApp(AppId& _appId, AppLibraryManager& _appLibraryManager, RouteTreeManager& _routeTreeManager)
{
    AppConfig& appCfg = FindAppConfigById(_appId);

    // Get AppTemplate
    AppTemplate& appTempate = _appLibraryManager.FindApp(appCfg.GetAppName());

    // Deploy App RouteTree
    DeployAppRouteTree(appCfg, appTempate, _routeTreeManager);

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

void AppDeploymentManager::DeployAppRouteTree(AppConfig& _appConfig, AppTemplate& _appTemplate, RouteTreeManager& _routeTreeManager)
{
    for (RouteDeployment& appRouteConfig : _appConfig.GetRouteDeployments())
    {
        AppNodeTemplate& appRoute = _appTemplate.GetAppNodeById(appRouteConfig.GetAppNodeId());

        _routeTreeManager.DeployAppRoute(appRouteConfig, appRoute);
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