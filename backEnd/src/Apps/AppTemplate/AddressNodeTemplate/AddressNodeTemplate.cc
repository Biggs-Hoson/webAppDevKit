

#include "AddressNodeTemplate.h"
#include <string>

AddressNodeTemplate::AddressNodeTemplate()
{
    RegisterStringField("path", &MatchCriteria);

    RegisterObjectArrayElement("subPaths", &SubRoutes);
};

std::string AddressNodeTemplate::GetMatchCritera()
{
    return MatchCriteria;
}

std::vector<AddressNodeTemplate>& AddressNodeTemplate::GetSubRoutes()
{
    return SubRoutes;
}