#include "PostData.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>

int GetContentLength()
{
	auto value = std::getenv("CONTENT_LENGTH");
	return value == nullptr ? 0 : std::atoi(value);
}

bool IsContentTypeFormPostData()
{
	auto value = std::getenv("CONTENT_TYPE");
	return value != nullptr && std::strcmp(value, "application/x-www-form-urlencoded") == 0;
}

std::string GetFormPostData()
{
	auto contentLength = GetContentLength();
	if (contentLength < 1 || !IsContentTypeFormPostData())
		return {};
	std::vector<char> buffer(contentLength);
	auto bytesRead = std::fread(buffer.data(), sizeof(char), contentLength, stdin);
	return { buffer.data(), bytesRead };
}

PostData::PostData()
	: FormData(GetFormPostData())
{
}

