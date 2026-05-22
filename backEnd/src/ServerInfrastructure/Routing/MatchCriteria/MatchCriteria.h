#ifndef matchCriteria
#define matchCriteria

#include <string>
#include <vector>

class MatchCriteria {
	public: 
        virtual bool MatchRequest(
			std::vector<std::string>::iterator&
		) = 0;
};

class MatchStaticString : public MatchCriteria {
	public:
    	MatchStaticString(const std::string);

        bool MatchRequest(
			std::vector<std::string>::iterator&
		) override;

	private:
    	std::string MatchString;
};

class MatchAny : public MatchCriteria {
	public:
		MatchAny();
        bool MatchRequest(
			std::vector<std::string>::iterator&
		) override;
};

#endif