#ifndef tableTemplate
#define tableTemplate

#include "../../../../ComponentClasses/JsonToClass/JsonToClass.h"

class TableTemplate : public JsonToClass
{
    public:
        TableTemplate(const Json::Value&);

    protected:
        void CollectChildErrors(std::vector<std::string>&, std::string) override;
    

};

#endif