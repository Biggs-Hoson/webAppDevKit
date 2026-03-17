#ifndef appManager
#define appManager

#include <string>

class AppManager {
	
    public:
	    AppManager();

	    void registerApp(string appName);

	    string createApp(string appName); // creates app components and returns appId

	    void getApps();

	    void runApp(string appId);

    private:
	    Json::Value openAppJSON();

	    int currentAppId = 0;
};

#endif