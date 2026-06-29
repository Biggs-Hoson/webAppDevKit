#ifndef AddressNode
#define AddressNode

#include <drogon/drogon.h>
#include <memory>
#include <string>

#include "../../../Apps/AppTemplate/AppNodeTemplate/AppNodeTemplate.h"
#include "../RoutingContext/RoutingContext.h"
#include "../AddressNodeAddress/AddressNodeAddress.h"


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

		std::vector<std::unique_ptr<AddressNode>> SubRoutes; // Automatically routed in if any RequestedRoute.RoutingComplete() == false

		virtual void CreateSubRoute(AddressNodeTemplate);

		bool IsAppNode;
		
		virtual AddressNode* AddressFound(AddressNodeAddress&, bool);
};

#endif