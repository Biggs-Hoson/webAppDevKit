#ifndef jsonToClass
#define jsonToClass


#include <drogon/drogon.h>
#include <optional>


struct KeyCheck {
    std::string Key;
    Json::ValueType ValueType;

    bool KeyRequired;
    
    std::optional<std::function<void(const Json::Value&)>> ParserFunction = std::nullopt;
};

class JsonToClass
{
    public:
        void ParseJson(const Json::Value&);

        // Colects errors vectors from the local JsonErrors vector 
        // into the first parameter along with calling
        // CollectChildErrors
        void CollectErrors(
            std::vector<std::string>&,
            std::string = "/");
        
        void PrintErrors();

    protected:
        std::vector<KeyCheck> ExpectedKeys; // Beware this means that you can expect duplicate keys

        std::vector<std::string> JsonErrors;

        virtual void CollectChildErrors(std::vector<std::string>&, std::string) = 0;

};


#endif