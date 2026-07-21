#ifndef addressNodeTemplate
#define addressNodeTemplate

#include "json/value.h"
#include <optional>
#include <string>
#include <vector>

#include <drogon/drogon.h>
#include "../../../ComponentClasses/JsonDeserializedObject/JsonDeserializedObject.h"


class AddressNodeTemplate : public JsonDeserializedObject
{
    public:

        AddressNodeTemplate();

        std::string GetMatchCritera();

        std::vector<AddressNodeTemplate>& GetSubRoutes();

    private:
        std::string MatchCriteria;

        std::vector<AddressNodeTemplate> SubRoutes;
        
};

#endif