#include "UtilityFunctions.h"
#include <sstream>

std::vector<std::string> SplitStringOnChar(
    std::string& splitString, 
    char delimiter
)
{
    std::vector<std::string> outputVector;
    std::stringstream ss(splitString);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        if (!item.empty())
            outputVector.push_back(item);
    }

    return outputVector;
};