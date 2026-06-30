#ifndef domainNode
#define domainNode

#include <memory>

#include "../AddressNode.h"

#include "../../Requested/RequestedPath/RequestedPath.h"

class DomainNode : public AddressNode
{
	public: 
		int ResolveRequest(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		) override;

		void CreateSubRoute(
			AddressNodeTemplate _subNodeTemplate
		) override;


    private:
        std::vector<AddressNode> PathNodes;

        int RoutePath(
            const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&, 
			RequestedRoute*
        );

		int HitEndpoint(
			const drogon::HttpRequestPtr&,
			drogon::HttpResponsePtr&
		);

		AddressNode* AddressFound(AddressNodeAddress&, bool) override;
};


#endif