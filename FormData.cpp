#include "FormData.h"
#include "StringUtility.h"
#include "HtmlUtility.h"
#include <cstdlib>

FormData::FormData(const std::string& urlEncodedFormData)
{
	auto valuePairs = String::Split(urlEncodedFormData, "&");
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

const FormData::ValueType& FormData::operator[](const std::string& key) const
{
	static const ValueType missingValue;
	auto iter = values.find(key);
	return iter == values.end() ? missingValue : iter->second;
}

const std::string& FormData::operator()(const std::string& key) const
{
	static const std::string missingValue;
	auto& value = operator[](key);
	return value.empty() ? missingValue : value[0];
}

FormData::IteratorType FormData::begin() const
{
	return values.begin();
}

FormData::IteratorType FormData::end() const
{
	return values.end();
}

