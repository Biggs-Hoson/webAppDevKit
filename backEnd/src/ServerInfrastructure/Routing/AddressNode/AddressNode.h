#ifndef addressNode
#define addressNode

#include <drogon/drogon.h>
#include <memory>
#include <string>

#include "../AddressNodeChildren/AddressNodeChildren.h"
#include "../MatchCriteria/MatchCriteria.h"

class RoutingContext;

class AddressNode : public AddressNodeChildren {
	public:
		// ---------- Constructor and Setup Functions ---------- //
		AddressNode(AddressNodeTemplate&);

		virtual ~AddressNode() {};

		void StructureFromTemplate(AddressNodeTemplate&);

		// ---------- Routing Function ---------- //
		bool RouteRequest(RoutingContext*);
        
		MatchCriteria* GetMatchCritera();

	protected:
        std::unique_ptr<MatchCriteria> MatchCriteraPtr;

		

		bool IsAppNode;
};

#endif