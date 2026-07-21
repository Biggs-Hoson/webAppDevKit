#ifndef jsonDeserializedObject
#define jsonDeserializedObject

#include "json/value.h"
#include <drogon/drogon.h>
#include <functional>
#include <map>
#include <optional>

// Register fields using pointer assignment
#define FIELD_TYPE_PTR(TypeName)			                \
    template <typename T>                                   \
	void Register##TypeName##Field(const std::string, T*);

#define REGISTER_FIELD_TYPE_PTR(TypeName)		\
	FIELD_TYPE_PTR(TypeName)			        \
	FIELD_TYPE_PTR(Optional##TypeName)

// Register fields using function parsers
#define REGISTER_FIELD_TYPE_FUNCTIONS(TypeName, Type) 		    \
	void Register##TypeName##Field(const std::string,	        \
        std::function<void(Type)>); 				            \
	void RegisterOptional##TypeName##Field(const std::string,	\
        std::function<void(Type)>); 				            \
	void RegisterOptional##TypeName##Field(const std::string,	\
        std::function<int(Type)>);

// Integer return on parsing functions used for validation within ParsingRules set
// Parsing functions are executed in a try catch loop where whatever error is caught is entered into the errors 

#define REGISTER_FIELD_TYPE(TypeName, Type)       	\
	REGISTER_FIELD_TYPE_PTR(TypeName)			\
	REGISTER_FIELD_TYPE_FUNCTIONS(TypeName, Type)

#define SIMPLE_TYPES_LIST(M)	\
    M(Int, int)                 \
    M(UnsignedInt, unsigned)	\
    M(Float, float)			    \
    M(String, std::string)		\
    M(Boolean, bool)

// ----- Array Versions Of Above ----- //

// Register fields using pointer assignment
#define REGISTER_ARRAY_FIELD_TYPE_PTR(TypeName)			                        \
    template <typename T>                                               \
	void Register##TypeName##ArrayElement(const std::string, std::vector<T>*);

// Register fields using function parsers
#define REGISTER_ARRAY_FIELD_TYPE_FUNCTIONS(TypeName, Type) 		    \
	void Register##TypeName##ArrayElement(const std::string,	\
        std::function<void(Type)>); 				            \
	void Register##TypeName##ArrayElement(const std::string,	\
        std::function<int(Type)>);

// Integer return on parsing functions used for validation within ParsingRules set
// Parsing functions are executed in a try catch loop where whatever error is caught is entered into the errors 

#define REGISTER_ARRAY_FIELD_TYPE(TypeName, Type)       	\
	REGISTER_ARRAY_FIELD_TYPE_PTR(TypeName)			\
	REGISTER_ARRAY_FIELD_TYPE_FUNCTIONS(TypeName, Type)

#define SIMPLE_TYPES_LIST(M)	\
    M(Int, int)                 \
    M(UnsignedInt, unsigned)	\
    M(Float, float)			    \
    M(String, std::string)		\
    M(Boolean, bool)

class JsonDeserializationErrors
{
	public: 
		void AppendError(
            std::string,
            std::string);

	private:
		std::vector<std::pair<std::string, std::string>> Errors;

        void Test(const Json::Value&);
};

class JsonDeserializedObject
{
    public:
        JsonDeserializedObject()
        {
            RegisterStringField("test", &A);
        };

        std::string A;

    protected:
        // Called once at top level template class, and in sub-objects automatically
        int DeserializedJson(
            const Json::Value&, 
            JsonDeserializationErrors*,
            std::string = "/"); 

        void AddParsingRule(std::string, std::string);
        void RemoveParsingRule(std::string);
        

        // Non-specific type handler (4)
        // Intended to be used for fallback and edge cases
        REGISTER_FIELD_TYPE_FUNCTIONS(, const Json::Value&) 

        // Primitive type field registration functions (5 * 5)
		SIMPLE_TYPES_LIST(REGISTER_FIELD_TYPE)

        // Object type json fields via JsonDeserializedObject (2)
        void RegisterObjectField(
            const std::string, JsonDeserializedObject*);
        void RegisterOptionalObjectField(
            const std::string, JsonDeserializedObject*);

        // Object type json fields via function (3)
        REGISTER_FIELD_TYPE_FUNCTIONS(Object, const Json::Value&)

		// ----- Array Fields ----- //

        // Registered functions are applied elementwise,
        // Registered pointers are emplaced_back() elementwise

        // Non-specific type handler (2)
        REGISTER_ARRAY_FIELD_TYPE_FUNCTIONS(, const Json::Value&)

        // Primitive type field registration functions (5 * 3)
		SIMPLE_TYPES_LIST(REGISTER_ARRAY_FIELD_TYPE)

        // Object type json fields via JsonDeserializedObject (1)
        template <typename T>
	    void RegisterObjectArrayElement(const std::string, std::vector<T>*);

        // Object type json fields via function (3)
        REGISTER_ARRAY_FIELD_TYPE_FUNCTIONS(Object, const Json::Value&)
        
	private:
            std::map<std::string, std::function<void(const Json::Value&)>> KeyParsers;
            std::map<std::string, std::string> ParsingRules; // rule, error message (for if parsing fails)
    		std::vector<std::string> ParsersUsed;
            std::string CurrentPath;

            std::map<std::string, std::string> JsonArrayIndex;

            JsonDeserializationErrors* ErrorsPtr;

            void RecordError(std::string, std::string = "");

            std::string GetJsonTypeName(Json::ValueType&);

            void ParseKey(
                const Json::Value&,
                Json::ValueType&,
                std::string,
                std::string = ""
            );
};

#include "./JsonDeserializedObjectParsers.tpp"

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