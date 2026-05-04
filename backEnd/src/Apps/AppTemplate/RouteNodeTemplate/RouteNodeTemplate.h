#ifndef routeNodeTemplate
#define routeNodeTemplate

#include <optional>
#include <string>
#include <vector>

#include <drogon/drogon.h>
#include "../../../JsonToTemplate/JsonToTemplate.h"


class RouteNodeTemplate : public JsonToTemplate
{
    public:
        RouteNodeTemplate(const std::optional<const Json::Value>&);

    protected:
        void CollectChildErrors(std::vector<std::string>&, std::string) override;

    private:
        std::string MatchCriteria;

        void ParseSubRoutes(const Json::Value&);

        std::vector<RouteNodeTemplate> SubRoutes;
};

#endif