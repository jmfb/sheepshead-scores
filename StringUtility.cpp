#include "StringUtility.h"
#include <iterator>
#include <algorithm>

namespace String
{

std::vector<std::string> Split(const std::string& value, const std::string& separator)
{
	std::vector<std::string> result;
	for (auto index = 0ul; index != std::string::npos && index < value.size(); )
	{
		auto end = value.find(separator, index);
		if (end == std::string::npos)
		{
			result.push_back(value.substr(index));
			index = std::string::npos;
		}
		else
		{
			result.push_back(value.substr(index, end - index));
			index = end + separator.size();
		}
	}
	if (result.empty())
		result.push_back({});
	return result;
}

std::string Replace(const std::string& value, const std::string& find, const std::string& replace)
{
	if (find.empty())
		return value;
	auto result = value;
	auto index = result.find(find);
	while (index != std::string::npos)
	{
		result.replace(index, find.size(), replace);
		index = result.find(find, index + replace.size());
	}
	return result;
}

std::string ToLower(const std::string& value)
{
	std::string result;
	std::transform(
		value.begin(),
		value.end(),
		std::back_inserter(result),
		[](char ch){ return std::tolower(ch); });
	return result;
}

}

