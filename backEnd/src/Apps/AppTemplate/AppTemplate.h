#ifndef appTemplate
#define appTemplate

#include "json/value.h"
#include <drogon/drogon.h>
#include <string>

#include "AppNodeTemplate/AppNodeTemplate.h"
#include "../../ComponentClasses/JsonToClass/JsonToClass.h"
#include "../AppComponents/AppVersion/AppVersion.h"

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

class AppTemplate : public JsonToClass
{
    public:
        AppTemplate(Json::Value&); // For now, construct using AppJson

        AppNodeTemplate& GetAppNodeById(int);

        std::string GetHash();

        std::string GetName();

        AppVersion& GetVersion();

    protected:
        void CollectChildErrors(std::vector<std::string>&, std::string) override;

    private:

        // Metadata fields
        std::string AppName;
        void ParseAppName(const Json::Value&);

        AppVersion Version;
        void ParseAppVersion(const Json::Value&);

        // Front end fields
        std::vector<AppNodeTemplate> AppRouteNodes;
        void ParseRouteMap(const Json::Value&);

};

#endif