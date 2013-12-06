#include "QueryString.h"
#include "StringUtility.h"
#include "HtmlUtility.h"
#include <cstdlib>

QueryString::QueryString()
{
	auto rawQueryString = std::getenv("QUERY_STRING");
	auto queryString = rawQueryString == nullptr ? "" : rawQueryString;
	auto valuePairs = String::Split(queryString, "&");
	for (auto valuePair : valuePairs)
	{
		auto parts = String::Split(valuePair, "=");
		auto key = parts[0];
		std::string value;
		if (parts.size() > 1)
			value = parts[1];
		if (!key.empty() || !value.empty())
			values[Html::UrlDecode(key)].push_back(Html::UrlDecode(value));
	}
}

const QueryString::ValueType& QueryString::operator[](const std::string& key) const
{
	static const ValueType missingValue;
	auto iter = values.find(key);
	return iter == values.end() ? missingValue : iter->second;
}

QueryString::IteratorType QueryString::begin() const
{
	return values.begin();
}

QueryString::IteratorType QueryString::end() const
{
	return values.end();
}

