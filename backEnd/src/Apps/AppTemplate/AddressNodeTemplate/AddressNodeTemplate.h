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
        std::string GetMatchCritera() {return "hello";}
        std::vector<AddressNodeTemplate>& GetSubRoutes() {return SubRoutes;}

    /*
        AddressNodeTemplate(const std::optional<const Json::Value>&);

        

        std::vector<AddressNodeTemplate>& GetSubRoutes();

    protected:
        void CollectChildErrors(std::vector<std::string>&, std::string) override;

    private:
        std::string MatchCriteria;

        void ParseSubRoutes(const Json::Value&);

        void ParsePath(const Json::Value&);
        */
        std::vector<AddressNodeTemplate> SubRoutes;
        
};

#endif