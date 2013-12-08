#include "HttpRequest.h"
#include <cstdlib>

std::string GetScriptName()
{
	auto value = std::getenv("SCRIPT_NAME");
	return value == nullptr ? "" : value;
}

HttpRequest::HttpRequest()
{
	requestMethod = ::GetRequestMethod();
	scriptName = ::GetScriptName();
}

HttpRequestMethod HttpRequest::GetRequestMethod() const
{
	return requestMethod;
}

const std::string& HttpRequest::GetScriptName() const
{
	return scriptName;
}

const QueryString& HttpRequest::GetQueryString() const
{
	return queryString;
}

const PostData& HttpRequest::GetPostData() const	
{
	return postData;
}

