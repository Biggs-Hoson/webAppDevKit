#ifndef appDeploymentManager
#define appDeploymentManager

#include "../AppLibraryManager/AppLibraryManager.h"
#include "../RouteTreeManager/RouteTreeManager.h"
#include "../../Apps/AppConfig/AppConfig.h"
#include "../../Apps/AppComponents/AppId/AppId.h"

class AppDeploymentManager 
{
    public:
        AppDeploymentManager();

        std::vector<AppId> GetIdsList();

        void DeployApp(AppId&, AppLibraryManager&, RouteTreeManager&);

    private:
        std::vector<AppConfig> ConfiguredApps;

        AppConfig& FindAppConfigById(AppId&);

        void DeployAppRouteTree(
            AppConfig&,
            AppTemplate&,
            RouteTreeManager&);
};

#endif