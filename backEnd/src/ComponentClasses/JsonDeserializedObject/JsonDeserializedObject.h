#ifndef jsonDeserializedObject
#define jsonDeserializedObject

#include "json/value.h"
#include <drogon/drogon.h>
#include <functional>
#include <map>
#include <optional>

// Register fields using pointer assignment
#define FIELD_TYPE_PTR(TypeName, Type)			                \
	void Register##TypeName##Field(const std::string, Type*);

#define REGISTER_FIELD_TYPE_PTR(TypeName, Type)		\
	FIELD_TYPE_PTR(TypeName, Type)			        \
	FIELD_TYPE_PTR(Optional##TypeName, Type)

// Register fields using function parsers
#define FIELD_TYPE_FUNCTIONS(TypeName, Type) 		    \
	void Register##TypeName##Field(const std::string,	\
        std::function<void(Type)>); 				    \
	void Register##TypeName##Field(const std::string,	\
        std::function<int(Type)>);

// Integer return on parsing functions used for validation within ParsingRules set
// Parsing functions are executed in a try catch loop where whatever error is caught is entered into the errors 

#define REGISTER_FIELD_TYPE_FUNCTIONS(TypeName, Type)	\
	FIELD_TYPE_FUNCTIONS(TypeName, Type)			    \
	FIELD_TYPE_FUNCTIONS(Optional##TypeName, Type)

#define REGISTER_FIELD_TYPE(TypeName, Type)       	\
	REGISTER_FIELD_TYPE_PTR(TypeName, Type)			\
	REGISTER_FIELD_TYPE_FUNCTIONS(TypeName, Type)

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
    protected:
        // Called once at top level template class, and in sub-objects automatically
        int DeserializedJson(
            const Json::Value&, 
            JsonDeserializationErrors*,
            std::string = "/"); 

        void AddParsingRule(std::string, std::string);
        void RemoveParsingRule(std::string);
        

        // Non-specific type handler (2 * 2)
        REGISTER_FIELD_TYPE_FUNCTIONS(, const Json::Value&) 

        // Primitive type field registration functions (5 * 6)
		SIMPLE_TYPES_LIST(REGISTER_FIELD_TYPE)

        // Object type json fields (2)
        REGISTER_FIELD_TYPE_PTR(Object, JsonDeserializedObject)

		// ----- Array Fields ----- //

        // Underlying Functions for arrays of:
        // Homogenous primitive: Direct assignment
        // Homogenous primitive: Function Applied ElementWise
        // Homogenous Object: Creation and use of .DeserializedJson(ArrElement)
        // - For a function, use the generic function
        // Anything else can use the elementwise handler function defined below:

        // Generic Function applied elementwise
        REGISTER_FIELD_TYPE_FUNCTIONS(Array, const Json::Value&)

        // How are rules made for arrays? (maybe just keep them simple)
        

	private:
            std::map<std::string, std::function<void(const Json::Value&)>> KeyParsers;
            std::map<std::string, std::string> ParsingRules; // rule, error message (for if parsing fails)
    		std::vector<std::string> ParsersUsed;
            std::string CurrentPath;

            JsonDeserializationErrors* ErrorsPtr;

            void RecordError(std::string, std::string = "");

            std::string GetJsonTypeName(Json::ValueType);
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