#ifndef jsonToClass
#define jsonToClass


#include <drogon/drogon.h>
#include <functional>
#include <map>
#include <optional>


struct KeyPaser{
    Json::ValueType ValueType;
    bool KeyRequired;
    std::function<void(const Json::Value&)> ParserFunction;
};

class JsonToClass
{
    public:
        JsonToClass(std::string);

        void ParseJson(const Json::Value&);

        // Colects errors vectors from the local JsonErrors vector 
        // into the first parameter along with calling
        // CollectChildErrors
        void CollectErrors(
            std::vector<std::string>&,
            std::string = "/");
        
        void PrintErrors();

    protected:

        std::string KeyName; // Key to append to field address

        void RemoveField(std::string);
        
        std::map<std::string, KeyPaser> KeyParsers; // Beware this means that you can expect duplicate keys

        std::vector<std::string> JsonErrors;

        virtual void CollectChildErrors(std::vector<std::string>&, std::string) = 0;


        // Json Parse Functions

        // Strings by value
        void RegisterString(const std::string, std::string*, bool);
        void RegisterStringField(const std::string, std::string*);
        void RegisterOptionalStringField(const std::string, std::string*);

        // String by function
        void RegisterString(const std::string, std::function<void(std::string)>&, bool);
        void RegisterStringField(const std::string, std::function<void(std::string)>&);
        void RegisterOptionalStringField(const std::string, std::function<void(std::string)>&);
        
        // Strings by value
        void RegisterInt(const std::string, int*, bool);
        void RegisterIntField(const std::string, int*);
        void RegisterOptionalIntField(const std::string, int*);

        // String by function
        void RegisterInt(const std::string, std::function<void(int)>&, bool);
        void RegisterIntField(const std::string, std::function<void(int)>&);
        void RegisterOptionalIntField(const std::string, std::function<void(int)>&);
        





};


#endif

/*

field name

Acceptor

// Try throw for anything that doesn't have a collect children:
intValue
uintValue
realValue
stringValue
booleanValue
arrayValue
objectValue


*/