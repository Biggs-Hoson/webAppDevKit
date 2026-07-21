

#include "AppNodeTemplate.h"

AppNodeTemplate::AppNodeTemplate()
{
    RemoveParsingRule("path:str");

    RegisterStringField("defaultRoute", &defaultDeployment);
};