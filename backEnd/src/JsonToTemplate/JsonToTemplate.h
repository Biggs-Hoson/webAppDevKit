#ifndef jsonToTemplate
#define jsonToTemplate


#include <drogon/drogon.h>
#include <optional>


struct KeyCheck {
    std::string Key;
    Json::ValueType ValueType;

    bool KeyRequired;
    
    std::optional<std::function<void(const Json::Value&)>> ParserFunction = std::nullopt;
};

class JsonToTemplate 
{
    public:
        void ParseJson(const Json::Value&);

        void CollectErrors(std::vector<std::string>&, std::string = "/");
        
        void PrintErrors();

    protected:
        std::vector<KeyCheck> ExpectedKeys; // Beware this means that you can expect duplicate keys

        std::vector<std::string> JsonErrors;

        virtual void CollectChildErrors(std::vector<std::string>&, std::string) = 0;

};


#endif