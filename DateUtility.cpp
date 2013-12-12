#include "DateUtility.h"
#include <ctime>

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

}

