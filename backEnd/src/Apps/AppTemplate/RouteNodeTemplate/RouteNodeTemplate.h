#ifndef AddressNodeTemplate
#define AddressNodeTemplate

#include <optional>
#include <string>
#include <vector>

#include <drogon/drogon.h>
#include "../../../ComponentClasses/JsonToClass/JsonToClass.h"


class AddressNodeTemplate : public JsonToClass
{
    public:
        AddressNodeTemplate(const std::optional<const Json::Value>&);

        std::string GetMatchCritera();

        std::vector<AddressNodeTemplate>& GetSubRoutes();

    protected:
        void CollectChildErrors(std::vector<std::string>&, std::string) override;

    private:
        std::string MatchCriteria;

        void ParseSubRoutes(const Json::Value&);

        std::vector<AddressNodeTemplate> SubRoutes;
};

#endif