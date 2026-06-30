#ifndef addressNode
#define addressNode

#include <drogon/drogon.h>
#include <memory>
#include <string>

#include "../../../Apps/AppTemplate/AppNodeTemplate/AppNodeTemplate.h"
#include "../AddressNodeAddress/AddressNodeAddress.h"

class RoutingContext;

class AddressNode {
	public:
		// ---------- Constructor and Setup Functions ---------- //
		AddressNode(AddressNodeTemplate&);

		void StructureFromTemplate(AddressNodeTemplate&);

		// ---------- Routing Function ---------- //
		bool RouteRequest(RoutingContext*);
        
		MatchCriteria* GetMatchCritera();

	protected:
        std::unique_ptr<MatchCriteria> MatchCriteraPtr;

		std::vector<std::unique_ptr<AddressNode>> SubRoutes; // Automatically routed in if RoutingContext.

		virtual void CreateSubRoute(AddressNodeTemplate);

		bool IsAppNode;
};

#endif