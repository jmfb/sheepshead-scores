#include "QueryString.h"
#include <cstdlib>

std::string GetQueryString()
{
	auto value = std::getenv("QUERY_STRING");
	return value == nullptr ? "" : value;
}

QueryString::QueryString()
	: FormData(GetQueryString())
{
}

