#include "./JsonDeserializedObject.h"
#include <string>


// Register fields using pointer assignment
#define CC_FIELD_TYPE_PTR(TypeName, Type, TypeSuffix, Operation)  \
    void JsonDeserializedObject::RegisterOptional##TypeName##Field(     \
        const std::string key, Type* target)                            \
        {                                                               \
            std::string parserName = key + "TypeSuffix";                \
            KeyParsers[parserName] =                                    \
                [target, parserName, this](const Json::Value& value)    \
                {									                    \
                    *target = value Operation;                          \
                    ParsersUsed.push_back(parserName);                  \
                };                                                      \
        }

#define CC_REGISTER_FIELD_TYPE_PTR(TypeName, Type, TypeSuffix, Operation)\
    CC_FIELD_TYPE_PTR(TypeName, Type, TypeSuffix, Operation)      \
    void JsonDeserializedObject::Register##TypeName##Field(             \
    const std::string key, Type* target)                            \
    {                                                               \
        std::string parserName = key + "TypeSuffix";                \
        AddParsingRule(parserName, parserName + "required");        \
        RegisterOptional##TypeName##Field(key, target);               \
    }


// Register fields using function parsers
#define CC_FIELD_TYPE_FUNCTIONS(TypeName, Type, TypeSuffix, Operation)  \
    void JsonDeserializedObject::RegisterOptional##TypeName##Field(     \
        const std::string key,	                                        \
        std::function<void(Type)>& func)                                \
        {                                                               \
            std::string parserName = key + "TypeSuffix";                \
            KeyParsers[parserName] =                                    \
                [func, parserName, this](const Json::Value& value)      \
                {									                    \
                    func(value Operation);                             \
                    ParsersUsed.push_back(parserName);                  \
                };                                                      \
        }                                                               \
    void JsonDeserializedObject::RegisterOptional##TypeName##Field(     \
        const std::string key,	                                        \
        std::function<int(Type)>& func)                                 \
        {                                                               \
            std::string parserName = key + "TypeSuffix";                \
            KeyParsers[parserName] =                                    \
                [func, parserName, this](const Json::Value& value)      \
                {			                                            \
                    int result = func(value Operation);                \
                    ParsersUsed.push_back(                              \
                        parserName + ":" + std::to_string(result));    \
                };                                                      \
        }


#define CC_REGISTER_FIELD_TYPE_FUNCTIONS(TypeName, Type, TypeSuffix, Operation)    \
    CC_FIELD_TYPE_FUNCTIONS(TypeName, Type, TypeSuffix, Operation)      \
    void JsonDeserializedObject::Register##TypeName##Field(             \
        const std::string key,	                                        \
        std::function<void(Type)>& func)                                \
        {                                                               \
            std::string parserName = key + "TypeSuffix";                \
            AddParsingRule(parserName, parserName + "required");        \
            RegisterOptional##TypeName##Field(key, func);               \
        }                                                               \
    void JsonDeserializedObject::Register##TypeName##Field(             \
        const std::string key,	                                        \
        std::function<int(Type)>& func)                                 \
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
    
// Primitive type field registration functions
CC_SIMPLE_TYPES_LIST(CC_REGISTER_FIELD_TYPE_FUNCTIONS)
CC_SIMPLE_TYPES_LIST(CC_REGISTER_FIELD_TYPE_PTR)


// Non-specific type handler
CC_REGISTER_FIELD_TYPE_FUNCTIONS(, const Json::Value&, ,)

// Child Objects

REGISTER_FIELD_TYPE_PTR(Object, JsonDeserializedObject*) // 2


void JsonDeserializedObject::RegisterObjectField(
    const std::string key, 
    JsonDeserializedObject* obj)
{
    std::string parserName = key + ":obj";
    KeyParsers[parserName] =
        [obj, parserName, this, key](const Json::Value& value)
        {
            int result = obj->DeserializedJson(
                value, ErrorsPtr, CurrentPath + key);
            ParsersUsed.push_back(parserName + ":" + std::to_string(result));
        };
}