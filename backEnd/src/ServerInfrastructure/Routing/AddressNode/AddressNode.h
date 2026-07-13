#ifndef addressNode
#define addressNode

#include <drogon/drogon.h>
#include <memory>
#include <string>

#include "../AddressNodeChildren/AddressNodeChildren.h"
#include "../../Endpoints/EndpointMap/EndpointMap.h"

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

		EndpointMap* GetEndpointMap();

		EndpointResolver* GetErrorResolver();

	protected:
        std::string MatchCritera;

		std::unique_ptr<EndpointMap> EndpointMapPtr;

		std::unique_ptr<EndpointResolver> ErrorResolverPtr;
		
        void CallIn() override;

		bool AppNode;

	private:
		void SetMatchCritera(std::string);
};

#endif