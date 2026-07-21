#include "AppVersion.h"

#include <sstream>
#include <string>
#include <vector>

AppVersion::AppVersion(std::string _versionString)
{
    SetVersion(_versionString);
};



void AppVersion::SetVersion(std::string _versionString)
{
    std::stringstream ss(_versionString);
    std::string num;

    while (std::getline(ss, num, '.')) {
        if (!num.empty())
            VersionArray.push_back(std::stoi(num));
        }
}


// Returns true if this current one is latest


const std::vector<int>& AppVersion::GetVersion()
{
    return VersionArray;
};

// True if later version.
bool AppVersion::operator > (AppVersion& comparison)
{
    const std::vector<int>& ComparisonVersion = comparison.GetVersion();

    //If one of the version arrays is longer, assume the extra numbers are
    // more important, and assume that they are 0 on the other array.
    std::vector<int>::iterator ThisIterator = VersionArray.begin();
    std::vector<int>::iterator ComparisonIterator = VersionArray.begin();


    int diff = ComparisonVersion.size() - VersionArray.size(); // Positive if Comparison is longer.
    for (int i = 0; i > diff; i--)
    {
        // This version array is longer
        if (*ThisIterator > 0)
        {
            return true; // This is a later version.
        }

        ThisIterator++;
    }

    for (int i = 0; i < diff; i++)
    {
        // ComparisonVersion array is longer
        if (*ComparisonIterator > 0)
        {
            return false; // ComparisonVersion is a later version.
        }

        ComparisonIterator++;
    }

    while(true)
    {
        if (*ThisIterator > *ComparisonIterator)
        {
            return true;
        }
        else if (*ThisIterator < *ComparisonIterator)
        {
            return false;
        }

        if (ThisIterator == VersionArray.end())
        {
            // Versions are identical
            return false;
        }
    }
}

bool AppVersion::operator == (AppVersion& comparison)
{
    const std::vector<int>& ComparisonVersion = comparison.GetVersion();

    //If one of the version arrays is longer, assume the extra numbers are
    // more important, and assume that they are 0 on the other array.
    std::vector<int>::iterator ThisIterator = VersionArray.begin();
    std::vector<int>::iterator ComparisonIterator = VersionArray.begin();


    int diff = ComparisonVersion.size() - VersionArray.size(); // Positive if Comparison is longer.
    for (int i = 0; i > diff; i--)
    {
        // This version array is longer
        if (*ThisIterator > 0)
        {
            return false;
        }

        ThisIterator++;
    }

    for (int i = 0; i < diff; i++)
    {
        // ComparisonVersion array is longer
        if (*ComparisonIterator > 0)
        {
            return false; // ComparisonVersion is a later version.
        }

        ComparisonIterator++;
    }

    while(true)
    {
        if (*ThisIterator > *ComparisonIterator)
        {
            return false;
        }
        else if (*ThisIterator < *ComparisonIterator)
        {
            return false;
        }

        if (ThisIterator == VersionArray.end())
        {
            // Versions are identical
            return true;
        }
    }
}


void AppVersion::operator = (std::string other)
{
    SetVersion(other);
}