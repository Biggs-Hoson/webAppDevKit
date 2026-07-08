#ifndef serverContextProvider
#define serverContextProvider

class ServerCentralManager;

class ServerContextProvider
{
    public:
        ServerContextProvider();

        ServerCentralManager* GetServerCentralManager();
};

#endif