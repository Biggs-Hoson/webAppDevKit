#ifndef addressNode
#define addressNode

#include <drogon/drogon.h>
#include <memory>
#include <string>

#include "../AddressNodeChildren/AddressNodeChildren.h"

class RoutingContext;

class AddressNode : public virtual AddressNodeChildren {
	public:
		// ---------- Constructor and Setup Functions ---------- //
		AddressNode(AddressNodeTemplate&);

		AddressNode(std::string);

		virtual ~AddressNode() {};

		void StructureFromTemplate(AddressNodeTemplate&);

		// ---------- Routing Function ---------- //
		bool RouteRequest(RoutingContext*);
        
		std::string GetMatchCritera();

		bool IsAppNode();

	protected:
        std::string MatchCritera;
		
        void CallIn() override;
		bool AppNode;

	private:
		void SetMatchCritera(std::string);
};

#endif