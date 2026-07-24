#include "./DatabaseObjectsTemplate.h"
#include "TableTemplate/TableTemplate.h"
#include "json/value.h"

DatabaseObjectsTemplate::DatabaseObjectsTemplate(const Json::Value& dboJson)
{
    //Register ExpectedKeys
    RegisterObjectArrayElement("relationalData", Tables);
};