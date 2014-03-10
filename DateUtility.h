#pragma once
#include <string>

namespace Date
{
	std::string GetToday();
	std::string GetBeginningOfMonth();
	std::string GetBeginningOfYear();
	std::string GetBeginningOfPeriod(const std::string& period);
	std::string GetEndOfPeriod(const std::string& period);
}
