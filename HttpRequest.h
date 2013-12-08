#pragma once
#include "HttpRequestMethod.h"
#include "QueryString.h"
#include "PostData.h"
#include <string>

class HttpRequest
{
public:
	HttpRequest();
	HttpRequest(const HttpRequest& rhs) = default;
	~HttpRequest() = default;
	
	HttpRequest& operator=(const HttpRequest& rhs) = default;
	
	HttpRequestMethod GetRequestMethod() const;
	const std::string& GetScriptName() const;
	const QueryString& GetQueryString() const;
	const PostData& GetPostData() const;	
	
private:
	HttpRequestMethod requestMethod;
	std::string scriptName;
	QueryString queryString;
	PostData postData;
};

