#include "AppId.h"

AppId::AppId() {};

AppId::AppId(std::string _appId)
{
    SetId(_appId);
};

void AppId::SetId(std::string _appId)
{
    // Check for valid AppId

    AppIdString = _appId;
};

std::string AppId::GetIdString()
{
    return AppIdString;
};

bool AppId::operator == (AppId& comparison)
{
    return comparison.GetIdString() == AppIdString;
};