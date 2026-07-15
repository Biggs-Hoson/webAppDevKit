#include "JsonToClass.h"
#include "json/value.h"


// String Parsers

void JsonToClass::RegisterString(const std::string key, std::string* target, bool required)
{
    KeyParsers[key] = {
        Json::stringValue,
        required,
        [target](const Json::Value& _jsonObject)
        {*target = _jsonObject.asString();}
    };
}

void JsonToClass::RegisterStringField(const std::string key, std::string* target)
{ RegisterString(key, target, true); };
void JsonToClass::RegisterOptionalStringField(const std::string key, std::string* target)
{ RegisterString(key, target, false); };


void JsonToClass::RegisterString(const std::string key, std::function<void(std::string)>& func, bool required)
{
    KeyParsers[key] = {
        Json::stringValue,
        required,
        [func](const Json::Value& _jsonObject)
        {func(_jsonObject.asString());}
    };
};

void JsonToClass::RegisterStringField(const std::string key, std::function<void(std::string)>& func)
{ RegisterString(key, func, true); };
void JsonToClass::RegisterOptionalStringField(const std::string key, std::function<void(std::string)>& func)
{ RegisterString(key, func, false); };


// Integer Parsers

void JsonToClass::RegisterInt(const std::string key, int* target, bool required)
{
    KeyParsers[key] = {
        Json::intValue,
        required,
        [target](const Json::Value& _jsonObject)
        {*target = _jsonObject.asInt();}
    };
};

void JsonToClass::RegisterIntField(const std::string key, int* target)
{ RegisterInt(key, target, true); }
void JsonToClass::RegisterOptionalIntField(const std::string key, int* target)
{ RegisterInt(key, target, false); }


void JsonToClass::RegisterInt(const std::string key, std::function<void(int)>& func, bool required)
{
    KeyParsers[key] = {
        Json::intValue,
        required,
        [func](const Json::Value& _jsonObject)
        {func(_jsonObject.asInt());}
    };
};

void JsonToClass::RegisterIntField(const std::string key, std::function<void(int)>& func)
{ RegisterInt(key, func, true);}
void JsonToClass::RegisterOptionalIntField(const std::string key, std::function<void(int)>& func)
{ RegisterInt(key, func, false);}


// Unsigned Integer Parsers

void JsonToClass::RegisterUInt(const std::string key, unsigned* target, bool required)
{
    KeyParsers[key] = {
        Json::uintValue,
        required,
        [target](const Json::Value& _jsonObject)
        {*target = _jsonObject.asInt();}
    };
};

void JsonToClass::RegisterUIntField(const std::string key, unsigned* target)
{ RegisterUInt(key, target, true); }
void JsonToClass::RegisterOptionalUIntField(const std::string key, unsigned* target)
{ RegisterUInt(key, target, false); }


void JsonToClass::RegisterUInt(const std::string key, std::function<void(unsigned)>& func, bool required)
{
    KeyParsers[key] = {
        Json::uintValue,
        required,
        [func](const Json::Value& _jsonObject)
        {func(_jsonObject.asUInt());}
    };
};

void JsonToClass::RegisterUIntField(const std::string key, std::function<void(unsigned)>& func)
{ RegisterUInt(key, func, true);}
void JsonToClass::RegisterOptionalUIntField(const std::string key, std::function<void(unsigned)>& func)
{ RegisterUInt(key, func, false);}


// Boolean Parsers

void JsonToClass::RegisterBoolean(const std::string key, bool* target, bool required)
{
    KeyParsers[key] = {
        Json::booleanValue,
        required,
        [target](const Json::Value& _jsonObject)
        {*target = _jsonObject.asBool();}
    };
};

void JsonToClass::RegisterBooleanField(const std::string key, bool* target)
{ RegisterUInt(key, target, true); }
void JsonToClass::RegisterOptionalBooleanField(const std::string key, bool* target)
{ RegisterUInt(key, target, false); }


void JsonToClass::RegisterBoolean(const std::string key, std::function<void(bool)>& func, bool required)
{
    KeyParsers[key] = {
        Json::booleanValue,
        required,
        [func](const Json::Value& _jsonObject)
        {func(_jsonObject.asBool());}
    };
};

void JsonToClass::RegisterBooleanField(const std::string key, std::function<void(bool)>& func)
{ RegisterUInt(key, func, true);}
void JsonToClass::RegisterOptionalBooleanField(const std::string key, std::function<void(bool)>& func)
{ RegisterUInt(key, func, false);}


// Array Parsers
template <typename T>
void JsonToClass::RegisterArray(const std::string key, std::vector<T>* target, bool required)
{
    KeyParsers[key] = {
        Json::arrayValue,
        required,
        [target](const Json::Value& _jsonObject)
        {*target = _jsonObject.asInt();}
    };
};

void JsonToClass::RegisterArrayField(const std::string key, unsigned* target)
{ RegisterUInt(key, target, true); }
void JsonToClass::RegisterOptionalArrayField(const std::string key, unsigned* target)
{ RegisterUInt(key, target, false); }


void JsonToClass::RegisterArray(const std::string key, std::function<void(unsigned)>& func, bool required)
{
    KeyParsers[key] = {
        Json::arrayValue,
        required,
        [func](const Json::Value& _jsonObject)
        {func(_jsonObject.asUInt());}
    };
};

void JsonToClass::RegisterArrayField(const std::string key, std::function<void(unsigned)>& func)
{ RegisterUInt(key, func, true);}
void JsonToClass::RegisterOptionalArrayField(const std::string key, std::function<void(unsigned)>& func)
{ RegisterUInt(key, func, false);}


// Object Parsers

void JsonToClass::RegisterUInt(const std::string key, unsigned* target, bool required)
{
    KeyParsers[key] = {
        Json::stringValue,
        required,
        [target](const Json::Value& _jsonObject)
        {*target = _jsonObject.asInt();}
    };
};

void JsonToClass::RegisterUIntField(const std::string key, unsigned* target)
{ RegisterUInt(key, target, true); }
void JsonToClass::RegisterOptionalUIntField(const std::string key, unsigned* target)
{ RegisterUInt(key, target, false); }


void JsonToClass::RegisterInt(const std::string key, std::function<void(unsigned)>& func, bool required)
{
    KeyParsers[key] = {
        Json::stringValue,
        required,
        [func](const Json::Value& _jsonObject)
        {func(_jsonObject.asUInt());}
    };
};

void JsonToClass::RegisterIntField(const std::string key, std::function<void(unsigned)>& func)
{ RegisterUInt(key, func, true);}
void JsonToClass::RegisterOptionalIntField(const std::string key, std::function<void(unsigned)>& func)
{ RegisterUInt(key, func, false);}