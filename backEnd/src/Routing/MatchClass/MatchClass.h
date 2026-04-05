#ifndef MATCH_CLASS_H
#define MATCH_CLASS_H

#include <string>

class MatchClass {
	public: 
        virtual int MatchRequest(std::string&) = 0;
};

class MatchStaticPath : public MatchClass {
	public:
    	MatchStaticPath(const std::string);

        int MatchRequest(std::string&) override;

	private:
    	std::string Path;
		
        int PathLength;
};

class MatchStaticDomain : public MatchClass {
	public:
    	MatchStaticDomain(const std::string);

        int MatchRequest(std::string&) override;

	private:
    	std::string Domain;
		
        int DomainLength;
};

#endif