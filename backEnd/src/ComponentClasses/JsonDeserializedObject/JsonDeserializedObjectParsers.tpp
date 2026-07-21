
// Register fields using pointer assignment
#define CC_FIELD_TYPE_PTR(TypeName, TypeSuffix, Operation)              \
    template <typename T>                                               \
    void JsonDeserializedObject::RegisterOptional##TypeName##Field(     \
        const std::string key, T* target)                               \
        {                                                               \
            std::string parserName = key + "TypeSuffix";                \
            KeyParsers[parserName] =                                    \
                [target, parserName, this](const Json::Value& value)    \
                {									                    \
                    *target = value Operation;                          \
                    ParsersUsed.emplace_back(parserName);                  \
                };                                                      \
        }

#define CC_REGISTER_FIELD_TYPE_PTR(                                     \
    TypeName, Type, TypeSuffix, Operation)                              \
    CC_FIELD_TYPE_PTR(TypeName, TypeSuffix, Operation)                  \
    template <typename T>                                               \
    void JsonDeserializedObject::Register##TypeName##Field(             \
    const std::string key, T* target)                                   \
    {                                                                   \
        std::string parserName = key + "TypeSuffix";                    \
        AddParsingRule(parserName, parserName + "required");            \
        RegisterOptional##TypeName##Field(key, target);                 \
    }


#define CC_SIMPLE_TYPES_LIST(M)	                \
    M(Int, int, :int, .asInt())                 \
    M(UnsignedInt, unsigned, :uint, .asUInt())	\
    M(Float, float, :real, .asFloat())			\
    M(String, std::string, :str, .asString())   \
    M(Boolean, bool, :bool, .asBool())           
    
CC_SIMPLE_TYPES_LIST(CC_REGISTER_FIELD_TYPE_PTR)

// ----- Array Regstration functions ----- //

// Register fields using pointer assignment
#define CC_REGISTER_ARRAY_FIELD_TYPE_PTR(TypeName, Type, TypeSuffix, Operation)              \
    template <typename T>                                               \
    void JsonDeserializedObject::Register##TypeName##ArrayElement(     \
        const std::string key, std::vector<T>* targetVector)            \
        {                                                               \
            std::string parserName = key + ":arr##TypeSuffix";          \
            KeyParsers[parserName] =                                    \
                [targetVector, parserName, this](const Json::Value& value)\
                {									                    \
                    targetVector->emplace_back(value Operation);        \
                    ParsersUsed.emplace_back(parserName);               \
                };                                                      \
        }

CC_SIMPLE_TYPES_LIST(CC_REGISTER_ARRAY_FIELD_TYPE_PTR)


// Child Objects
template <typename T>
void JsonDeserializedObject::RegisterObjectArrayElement(
    const std::string key, 
    std ::vector<T> * objectVector)
{
    std::string parserName = key + ":arr:obj";
    KeyParsers[parserName] =
        [objectVector, parserName, this, key](const Json::Value& value)
        {
            objectVector->emplace_back();
            int result = objectVector->back().DeserializedJson(
                value, ErrorsPtr, CurrentPath + key + JsonArrayIndex.at(key));
            ParsersUsed.emplace_back(parserName + ":" + std::to_string(result));
        };
}
