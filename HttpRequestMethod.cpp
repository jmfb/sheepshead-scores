#include "HttpRequestMethod.h"
#include <cstdlib>
#include <cstring>

HttpRequestMethod GetRequestMethod()
{
	auto value = std::getenv("REQUEST_METHOD");
	if (value == nullptr)
		return HttpRequestMethod::Other;
	if (std::strcmp(value, "GET") == 0)
		return HttpRequestMethod::Get;
	if (std::strcmp(value, "POST") == 0)
		return HttpRequestMethod::Post;
	return HttpRequestMethod::Other;
}

