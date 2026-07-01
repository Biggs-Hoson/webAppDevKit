#ifndef appDeploymentManager
#define appDeploymentManager

#include "../AppLibraryManager/AppLibraryManager.h"
#include "../AddressTreeManager/AddressTreeManager.h"
#include "../../Apps/AppConfig/AppConfig.h"
#include "../../Apps/AppComponents/AppId/AppId.h"

class AppDeploymentManager 
{
    public:
        AppDeploymentManager();

        std::vector<AppId> GetIdsList();

        void DeployApp(AppId&, AppLibraryManager&, AddressTreeManager&);

    private:
        std::vector<AppConfig> ConfiguredApps;

        AppConfig& FindAppConfigById(AppId&);

        void DeployAppAddresses(
            AppConfig&,
            AppTemplate&,
            AddressTreeManager&);
};

#endif