#include "drogon/HttpAppFramework.h"
#include "drogon/HttpController.h"
#include "drogon/HttpResponse.h"
#include "drogon/drogon.h"
#include <string>

using namespace drogon;
using std::string;

#define TEXT_RESP(txt) \
	auto resp = HttpResponse::newHttpResponse(); \
	resp->setBody(txt); \
	callback(resp)

// Will never get called, is overshadowed by G
class D : public HttpController<D>
{
public:
	void asyncHandleHttpRequest(
		const HttpRequestPtr& req,
		std::function<void (const HttpResponsePtr&)>&& callback,
		string&& id)
	{
		TEXT_RESP("D");
	}

	METHOD_LIST_BEGIN
		ADD_METHOD_TO(
			D::asyncHandleHttpRequest,
			"/api/clients/device-groups/{device-group-id}",
			HttpMethod::Get,
		);
	METHOD_LIST_END
};

// Will overshadow D
class G : public HttpController<G>
{
public:
	void asyncHandleHttpRequest(
		const HttpRequestPtr& req,
		std::function<void (const HttpResponsePtr&)>&& callback,
		string&& city,
		string&& id)
	{
		TEXT_RESP("G");
	}

	METHOD_LIST_BEGIN
		ADD_METHOD_TO(
			G::asyncHandleHttpRequest,
			"/api/clients/{user-group-city}/{user-group-id}",
			HttpMethod::Get,
		);
	METHOD_LIST_END
};

int main()
{
	app()
		.addListener("0.0.0.0", 8080)
		.run();
}
