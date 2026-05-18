#ifndef appId
#define appId

#include <string>

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