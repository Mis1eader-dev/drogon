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

class A : public HttpController<A>
{
public:
	void asyncHandleHttpRequest(
		const HttpRequestPtr& req,
		std::function<void (const HttpResponsePtr&)>&& callback,
		string&& city,
		string&& id)
	{
		TEXT_RESP("A");
	}

	METHOD_LIST_BEGIN
		ADD_METHOD_TO(
			A::asyncHandleHttpRequest,
			"/api/clients/{user-group-city}/{user-group-id}/users",
			HttpMethod::Get,
		);
	METHOD_LIST_END
};

class B : public HttpController<B>
{
public:
	void asyncHandleHttpRequest(
		const HttpRequestPtr& req,
		std::function<void (const HttpResponsePtr&)>&& callback,
		string&& dev)
	{
		TEXT_RESP("B");
	}

	METHOD_LIST_BEGIN
		ADD_METHOD_TO(
			B::asyncHandleHttpRequest,
			"/api/clients/device-groups/{device-group-id}/devices",
			HttpMethod::Get,
		);
	METHOD_LIST_END
};

class C : public HttpController<C>
{
public:
	void asyncHandleHttpRequest(
		const HttpRequestPtr& req,
		std::function<void (const HttpResponsePtr&)>&& callback,
		string&& city,
		string&& id,
		string&& dev)
	{
		TEXT_RESP("C");
	}

	METHOD_LIST_BEGIN
		ADD_METHOD_TO(
			C::asyncHandleHttpRequest,
			"/api/clients/{user-group-city}/{user-group-id}/device-groups/{device-group-id}/devices",
			HttpMethod::Get,
		);
	METHOD_LIST_END
};

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

class E : public HttpController<E>
{
public:
	void asyncHandleHttpRequest(
		const HttpRequestPtr& req,
		std::function<void (const HttpResponsePtr&)>&& callback,
		string&& city,
		string&& id,
		string&& dev)
	{
		TEXT_RESP("E");
	}

	METHOD_LIST_BEGIN
		ADD_METHOD_TO(
			E::asyncHandleHttpRequest,
			"/api/clients/{user-group-city}/{user-group-id}/device-groups/{device-group}",
			HttpMethod::Get,
		);
	METHOD_LIST_END
};

class F : public HttpController<F>
{
public:
	void asyncHandleHttpRequest(
		const HttpRequestPtr& req,
		std::function<void (const HttpResponsePtr&)>&& callback,
		string&& city,
		string&& id)
	{
		TEXT_RESP("F");
	}

	METHOD_LIST_BEGIN
		ADD_METHOD_TO(
			F::asyncHandleHttpRequest,
			"/api/clients/{user-group-city}/{user-group-id}/device-groups",
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
