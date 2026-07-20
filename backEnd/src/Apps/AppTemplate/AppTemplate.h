#ifndef appTemplate
#define appTemplate

#include "json/value.h"
#include <drogon/drogon.h>
#include <memory>
#include <string>

#include "AppNodeTemplate/AppNodeTemplate.h"
#include "../../ComponentClasses/JsonDeserializedObject/JsonDeserializedObject.h"
#include "../AppComponents/AppVersion/AppVersion.h"
#include "./DatabaseObjectsTemplate/DatabaseObjectsTemplate.h"

/* AppTemplate

The AppTemplate class is constructed from an App file.
It performs the nessecary schema and format checking of
the app Json, along with validation for the rest of the
content of the App File during this its instanciation. 

Upon instanciation, it stores a vector of all the errors.

The class then provides a set of getters and functions
containing the correctly typed fields and properties
of app.

*/



class AppTemplate : public JsonDeserializedObject
{
    public:
    
        AppTemplate(Json::Value&); // For now, construct using AppJson

        AppNodeTemplate& GetAppNodeById(int);

        std::string GetHash();

        std::string GetName();

        AppVersion& GetVersion();

    private:
        // Metadata fields
        std::string AppName;

        AppVersion Version;

        JsonDeserializationErrors DeserializationErrors;

        // Route Map:
        std::vector<AppNodeTemplate> AppAddressNodes;

        //Database Objects:
        DatabaseObjectsTemplate dboTemplate;

    /*

    private:

        void ParseAppName(const Json::Value&);

        void ParseAppVersion(const Json::Value&);

        // Front end fields
        void ParseRouteMap(const Json::Value&);

        std::shared_ptr<> ;
        void ParseDatabaseObjects(const Json::Value&);
*/
};

#endif