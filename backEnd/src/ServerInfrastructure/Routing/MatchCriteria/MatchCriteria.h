#ifndef matchCriteria
#define matchCriteria

#include <string>
#include <vector>
#include <memory>

class MatchCriteria {
	public: 
		MatchCriteria(std::string);

		static std::unique_ptr<MatchCriteria> GetMatchCriteraPtr(std::string);

        virtual bool MatchRequest(
			std::vector<std::string>::iterator&
		) = 0;
	
		std::string GetMatchString();
		
	protected:
		std::string MatchString;
};

class MatchStaticString : public MatchCriteria {
	public:
    	MatchStaticString(const std::string);

        bool MatchRequest(
			std::vector<std::string>::iterator&
		) override;
};

class MatchAny : public MatchCriteria {
	public:
		MatchAny();
        bool MatchRequest(
			std::vector<std::string>::iterator&
		) override;
};

#endif