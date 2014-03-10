#include "DateUtility.h"
#include <ctime>
#include <sstream>
#include <stdexcept>

namespace Date
{

std::string FormatToday(const char* format)
{
	auto time = std::time(nullptr);
	char buffer[100];
	std::strftime(buffer, sizeof(buffer), format, std::localtime(&time));
	return buffer;
}

std::string GetToday()
{
	return FormatToday("%Y-%m-%d");
}

std::string GetBeginningOfMonth()
{
	return FormatToday("%Y-%m-01");
}

std::string GetBeginningOfYear()
{
	return FormatToday("%Y-01-01");
}

std::string GetBeginningOfPeriod(const std::string& period)
{
	std::istringstream in(period);
	auto year = 0;
	auto month = 0;
	char separator = ' ';
	in >> year >> separator >> month;
	if (year < 1900 || year > 3000)
		throw std::runtime_error("Invalid year in period.");
	if (month < 0 || month > 12)
		throw std::runtime_error("Invalid month in period.");
	if (month == 0)
		return std::to_string(year) + "-01-01";
	return std::to_string(year) + "-" + std::to_string(month) + "-01";
}

std::string GetEndOfPeriod(const std::string& period)
{
	std::istringstream in(period);
	auto year = 0;
	auto month = 0;
	char separator = ' ';
	in >> year >> separator >> month;
	if (year < 1900 || year > 3000)
		throw std::runtime_error("Invalid year in period.");
	if (month < 0 || month > 12)
		throw std::runtime_error("Invalid month in period.");
	if (month == 0 || month == 12)
		return std::to_string(year + 1) + "-01-01";
	return std::to_string(year) + "-" + std::to_string(month + 1) + "-01";
}

}

