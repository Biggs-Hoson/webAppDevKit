#ifndef appVersion
#define appVersion

#include <vector>
#include <string>

class AppVersion
{
    public:
        AppVersion() {};

        AppVersion(std::string);

        void SetVersion(std::string);

        const std::vector<int>& GetVersion();

        bool operator > (AppVersion&);

        bool operator == (AppVersion&);

        void operator = (std::string);

    private:
        std::vector<int> VersionArray;
};

#endif