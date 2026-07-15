#ifndef manager
#define manager

class AddressTreeManager;
class AppDeploymentManager;
class AppLibraryManager;
class ServerCentralManager;
class DatabaseManager;

class Manager
{
    protected:
        static AddressTreeManager* AddressTreeManagerPtr;
        static AppDeploymentManager* AppDeploymentManagerPtr;
        static AppLibraryManager* AppLibraryManagerPtr;
        static ServerCentralManager* ServerCentralManagerPtr;
        static DatabaseManager* DatabaseManagerPtr;
};

#endif