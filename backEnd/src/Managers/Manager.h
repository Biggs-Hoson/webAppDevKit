#ifndef manager
#define manager

#include "../ServerInfrastructure/ServerContextProvider/ServerContextProvider.h"

class Manager
{
    public:
        Manager(ServerContextProvider* _provider) : ServerContextProviderPtr(_provider) {};

    protected:
        ServerContextProvider* ServerContextProviderPtr;
};

#endif