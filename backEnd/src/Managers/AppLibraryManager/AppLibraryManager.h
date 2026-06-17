#ifndef appManager
#define appManager

#include <optional>
#include <string>
#include <vector>
#include <drogon/drogon.h>
#include "../../ServerInfrastructure/Routing/AddressNode/AddressNode.h"
#include "../../Apps/AppTemplate/AppTemplate.h"

class AppLibraryManager
{
	public: 
    	AppLibraryManager();
        
		/* RegisterApp

		Takes the AppFile and creates an AppTemplate object based with it.

		Stores the AppFile in a map (FOR NOW: just store it against its name)
		
		*/
		void RegisterApp(std::string);
        
    	// Used to deploy an app to the server, structuring its database entities, and loading its config to the appconfig database along with anything else that needs to be done to deploy the app.
        // May also need to recover server state somehow from any lmdb & associated databases
    	void DeployApp(std::string);

        // Activates the endpoints for a deployed application
        void ActivateApp();
		
		AppTemplate FindApp(std::string, std::optional<AppVersion*> = std::nullopt) ;

	private:
		std::vector<AppTemplate> AppLibrary;

		// Finding AppTemplate
		AppTemplate FindAppTemplateLatest(std::string);
		AppTemplate FindAppTemplateByVersion(std::string, AppVersion*);
};


#endif