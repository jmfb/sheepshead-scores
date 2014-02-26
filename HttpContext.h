#pragma once
#include <string>

namespace Headers
{
	static auto ContentLength = "CONTENT_LENGTH";
	static auto ContentType = "CONTENT_TYPE";
}

namespace ContentTypes
{
	static auto Json = "application/json";
	static auto Form = "application/x-www-form-urlencoded";
}

class HttpContext
{
public:
	static std::string GetHeader(const std::string& name);
	
	static int GetContentLength();
	static std::string GetContentType();
	
	static std::string ReadPostData(int bytesToRead);
	
	static std::string ReadPostDataOfType(const std::string& contentType);
};

