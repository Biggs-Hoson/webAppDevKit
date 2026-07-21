#include "./JsonDeserializedObject.h"
#include <string>

// Register fields using function parsers
#define CC_REGISTER_FIELD_TYPE_FUNCTIONS(TypeName, Type, TypeSuffix, Operation)  \
    void JsonDeserializedObject::RegisterOptional##TypeName##Field(     \
        const std::string key,	                                        \
        std::function<void(Type)> func)                                 \
        {                                                               \
            std::string parserName = key + "TypeSuffix";                \
            KeyParsers[parserName] =                                    \
                [func, parserName, this](const Json::Value& value)      \
                {									                    \
                    func(value Operation);                              \
                    ParsersUsed.emplace_back(parserName);                  \
                };                                                      \
        }                                                               \
    void JsonDeserializedObject::RegisterOptional##TypeName##Field(     \
        const std::string key,	                                        \
        std::function<int(Type)> func)                                  \
        {                                                               \
            std::string parserName = key + "TypeSuffix";                \
            KeyParsers[parserName] =                                    \
                [func, parserName, this](const Json::Value& value)      \
                {			                                            \
                    int result = func(value Operation);                 \
                    ParsersUsed.emplace_back(                              \
                        parserName + ":" + std::to_string(result));     \
                };                                                      \
        }                                                               \
    void JsonDeserializedObject::Register##TypeName##Field(             \
        const std::string key,	                                        \
        std::function<void(Type)> func)                                 \
        {                                                               \
            std::string parserName = key + "TypeSuffix";                \
            AddParsingRule(parserName, parserName + "required");        \
            RegisterOptional##TypeName##Field(key, func);               \
        }



#define CC_SIMPLE_TYPES_LIST(M)	                \
    M(Int, int, :int, .asInt())                 \
    M(UnsignedInt, unsigned, :uint, .asUInt())	\
    M(Float, float, :real, .asFloat())			\
    M(String, std::string, :str, .asString())   \
    M(Boolean, bool, :bool, .asBool())           
    

// Non-specific type handler
CC_REGISTER_FIELD_TYPE_FUNCTIONS(, const Json::Value&, ,)

// Primitive type field registration functions
CC_SIMPLE_TYPES_LIST(CC_REGISTER_FIELD_TYPE_FUNCTIONS)



// Child Objects
void JsonDeserializedObject::RegisterOptionalObjectField(
    const std::string key, 
    JsonDeserializedObject* obj)
{
    std::string parserName = key + ":obj";
    KeyParsers[parserName] =
        [obj, parserName, this, key](const Json::Value& value)
        {
            int result = obj->DeserializedJson(
                value, ErrorsPtr, CurrentPath + key);
            ParsersUsed.emplace_back(parserName + ":" + std::to_string(result));
        };
}

void JsonDeserializedObject::RegisterObjectField(
    const std::string key, 
    JsonDeserializedObject* obj)
{
    std::string parserName = key + ":obj";
    AddParsingRule(parserName, parserName + "required");
    RegisterOptionalObjectField(key, obj);
}


// Object type json fields via function (4)
CC_REGISTER_FIELD_TYPE_FUNCTIONS(Object, const Json::Value&, :Obj, )



// ----- Array Regstration functions ----- //

// Register fields using function parsers
#define CC_REGISTER_ARRAY_FIELD_TYPE_FUNCTIONS(TypeName, Type, TypeSuffix, Operation)  \
    void JsonDeserializedObject                                         \
        ::Register##TypeName##ArrayElement(                     \
        const std::string key,	                                        \
        std::function<void(Type)> func)                                 \
        {                                                               \
            std::string parserName = key + ":arr##TypeSuffix";                \
            KeyParsers[parserName] =                                    \
                [func, parserName, this](const Json::Value& value)      \
                {									                    \
                    func(value Operation);                              \
                    ParsersUsed.emplace_back(parserName);                  \
                };                                                      \
        }                                                               \
    void JsonDeserializedObject                                         \
        ::Register##TypeName##ArrayElement(                     \
        const std::string key,	                                        \
        std::function<int(Type)> func)                                  \
        {                                                               \
            std::string parserName = key + ":arr##TypeSuffix";                \
            KeyParsers[parserName] =                                    \
                [func, parserName, this](const Json::Value& value)      \
                {			                                            \
                    int result = func(value Operation);                 \
                    ParsersUsed.emplace_back(                              \
                        parserName + ":" + std::to_string(result));     \
                };                                                      \
        }


// Non-specific type handler
CC_REGISTER_ARRAY_FIELD_TYPE_FUNCTIONS(, const Json::Value&, ,)

// Primitive type field registration functions
CC_SIMPLE_TYPES_LIST(CC_REGISTER_ARRAY_FIELD_TYPE_FUNCTIONS)

// Object type json fields via function (4)
CC_REGISTER_ARRAY_FIELD_TYPE_FUNCTIONS(Object, const Json::Value&, :Obj, )

