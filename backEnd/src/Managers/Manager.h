#ifndef manager
#define manager

class AddressTreeManager;
class AppDeploymentManager;
class AppLibraryManager;
class ServerCentralManager;

class Manager
{
    protected:
        static AddressTreeManager* AddressTreeManagerPtr;
        static AppDeploymentManager* AppDeploymentManagerPtr;
        static AppLibraryManager* AppLibraryManagerPtr;
        static ServerCentralManager* ServerCentralManagerPtr;
};

#endif