#ifndef AddressNode
#define AddressNode

#include <drogon/drogon.h>
#include <memory>
#include <string>

#include "../../../Apps/AppTemplate/AppNodeTemplate/AppNodeTemplate.h"
#include "../RequestedRoute/RequestedRoute.h"
#include "../AddressNodeAddress/AddressNodeAddress.h"



class AddressNode {
	public:
		AddressNode(AddressNodeTemplate&);

		int RouteRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
		);
        
		virtual int ResolveRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		);
		
		void StructureFromTemplate(AddressNodeTemplate&);

		virtual AddressNode* GetAddressNode(AddressNodeAddress&, bool = false);

		AddressNode* GetAddressNodeInSubRoutes(AddressNodeAddress&, bool = false);

	protected:
        std::unique_ptr<MatchCriteria> MatchCriteraPtr;

		bool MatchRequest(
			RequestedRoute*
		);

		std::vector<std::unique_ptr<AddressNode>> SubRoutes; // Automatically routed in if any RequestedRoute.RoutingComplete() == false

		bool RouteRequestInSubroutes(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
		);

		virtual void CreateSubRoute(AddressNodeTemplate);
		
		virtual AddressNode* AddressFound(AddressNodeAddress&, bool);
};

#endif