#include "AppDeploymentManager.h"

AppDeploymentManager::AppDeploymentManager()
{
    //Temp:
    std::string s = "{\n\"appId\": 0,\n\"appName\": \"myNotes\",\n\"appVersion\": \"1.2.3\",\n\"appHash\": \"abxyz\",\n\"appRouteDeployments\": [\n{\n\"routeId\": 0,\n\"domainId\": 0,\n\"subdomainRoute\": [],\n\"subpathRoute\": [\n    \"notes\"\n]\n}\n]\n}";
    
    Json::Value notesConfig(s);

    ConfiguredApps.push_back(AppConfig(notesConfig));
};

void AppDeploymentManager::DeployApp(AppId& _appId, AppLibraryManager& _appLibraryManager, RouteTreeManager& _routeTreeManager)
{
    AppConfig& appCfg = FindAppConfigById(_appId);


    // Get AppTemplate
    AppTemplate& appTempate = _appLibraryManager.FindApp(appCfg.GetAppName());

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

/*
{
    "appId": 0,
    "appName": "myNotes",
    "appVersion": "1.2.3",
    "appHash": "abxyz",
    "appRouteDeployments": [
        {
            "routeId": 0,
            "domainId": 0,
            "subdomainRoute": [],
            "subpathRoute": [
                "notes"
            ]
        }
    ]
}
*/