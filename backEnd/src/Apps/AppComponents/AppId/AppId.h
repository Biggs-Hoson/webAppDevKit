#ifndef appId
#define appId

#include <string>

// AppId refers to the ID of the deployed app, the AppHash is the aspect of the App file that is unchanged.
class AppId
{
    public:
        AppId();
        
        AppId(std::string);

        void SetId(std::string);

        std::string GetIdString();

        bool operator == (AppId&);

    private:
        std::string AppIdString;
};

#endif