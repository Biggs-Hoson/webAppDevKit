#ifndef routeNodeTemplate
#define routeNodeTemplate

#include <optional>
#include <string>
#include <vector>

#include <drogon/drogon.h>
#include "../../../ComponentClasses/JsonToClass/JsonToClass.h"


class RouteNodeTemplate : public JsonToClass
{
    public:
        RouteNodeTemplate(const std::optional<const Json::Value>&);

        std::string GetMatchCritera();

        std::vector<RouteNodeTemplate>& GetSubRoutes();

    protected:
        void CollectChildErrors(std::vector<std::string>&, std::string) override;

    private:
        std::string MatchCriteria;

        void ParseSubRoutes(const Json::Value&);

        std::vector<RouteNodeTemplate> SubRoutes;
};

#endif