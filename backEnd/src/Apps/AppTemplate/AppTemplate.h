#ifndef appTemplate
#define appTemplate

#include "json/value.h"
#include <drogon/drogon.h>
#include <string>

#include "AppNodeTemplate/AppNodeTemplate.h"
#include "../../JsonToTemplate/JsonToTemplate.h"

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

class AppTemplate : public JsonToTemplate
{
    public:
        AppTemplate(Json::Value&); // For now, construct using AppJson

    protected:
        void CollectChildErrors(std::vector<std::string>&, std::string) override;

    private:

        // Metadata parsing functions
        void ParseAppName(const Json::Value&);

        // Metadata fields
        std::string AppName;

        // Front end parsing functions
        void ParseRouteMap(const Json::Value&);

        // Front end fields
        std::vector<AppNodeTemplate> AppRouteNodes;

};

#endif