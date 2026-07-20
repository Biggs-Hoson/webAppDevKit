#ifndef databaseObjectsTemplate
#define databaseObjectsTemplate

#include "../../../ComponentClasses/JsonDeserializedObject/JsonDeserializedObject.h"
#include "./TableTemplate/TableTemplate.h"
#include "json/value.h"

class DatabaseObjectsTemplate : public JsonDeserializedObject
{
    /*
    public:
        DatabaseObjectsTemplate(const Json::Value&);

    protected:
        void CollectChildErrors(std::vector<std::string>&, std::string) override;
    
    private:
        std::vector<TableTemplate> Tables;
        void ParseRelationalDataTables(const Json::Value&);

        */
};


#endif