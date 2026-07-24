#ifndef tableTemplate
#define tableTemplate

#include "../../../../ComponentClasses/JsonDeserializedObject/JsonDeserializedObject.h"

class TableTemplate : public JsonDeserializedObject
{
    public:
        TableTemplate();

    private:
        std::string tableName;
        
    
};

#endif