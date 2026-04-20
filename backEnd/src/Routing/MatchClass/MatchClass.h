#ifndef MATCH_CLASS_H
#define MATCH_CLASS_H

#include <string>
#include <vector>

class MatchClass {
	public: 
        virtual bool MatchRequest(
			std::vector<std::string>::iterator&,
			std::vector<std::string>::iterator&
		) = 0;
};

class MatchStaticString : public MatchClass {
	public:
    	MatchStaticString(const std::string);

        bool MatchRequest(
			std::vector<std::string>::iterator&,
			std::vector<std::string>::iterator&
		) override;

	private:
    	std::string MatchString;
};

#endif