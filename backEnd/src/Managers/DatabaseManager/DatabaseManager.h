#ifndef databaseManager
#define databaseManager

#include "../Manager.h"

class DatabaseManager : public Manager {
    public:
        DatabaseManager();

        void CreateAppDatabaseObjects();

    private:


};

#endif