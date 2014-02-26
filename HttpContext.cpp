#include "HttpContext.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>

std::string HttpContext::GetHeader(const std::string& name)
{
	auto value = std::getenv(name.c_str());
	return value == nullptr ? "" : value;
}

int HttpContext::GetContentLength()
{
	auto value = GetHeader(Headers::ContentLength);
	return value.empty() ? 0 : std::stoi(value);
}

std::string HttpContext::GetContentType()
{
	return GetHeader(Headers::ContentType);
}

std::string HttpContext::ReadPostData(int bytesToRead)
{
	if (bytesToRead < 1)
		return {};
	std::vector<char> buffer(bytesToRead);
	auto bytesRead = std::fread(buffer.data(), sizeof(char), bytesToRead, stdin);
	return { buffer.data(), bytesRead };
}

std::string HttpContext::ReadPostDataOfType(const std::string& contentType)
{
	if (GetContentType().find(contentType) != 0)
		return {};
	return ReadPostData(GetContentLength());
}

