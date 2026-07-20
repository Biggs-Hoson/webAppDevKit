#ifndef databaseObjectsTemplate
#define databaseObjectsTemplate

#include "../../../ComponentClasses/JsonDeserializedObject/JsonDeserializedObject.h"
#include "./TableTemplate/TableTemplate.h"
#include "json/value.h"

class DatabaseObjectsTemplate : public JsonDeserializedObject
{
    
    public:
        DatabaseObjectsTemplate() {};

    /*
    private:
        std::vector<TableTemplate> Tables;
        void ParseRelationalDataTables(const Json::Value&);

        */
};


#endif