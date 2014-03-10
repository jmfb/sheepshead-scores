#pragma once
#include <string>
#include <vector>

namespace String
{
	std::vector<std::string> Split(const std::string& value, const std::string& separator);

	std::string Join(const std::vector<std::string>& values, const std::string& separator);
	
	std::string Replace(const std::string& value, const std::string& find, const std::string& replace);
	
	std::string ToLower(const std::string& value);
}

