#include "MonthModel.h"
#include <sstream>

MonthModel::MonthModel(const std::string& date)
{
	std::istringstream in(date);
	int year = 0;
	int month = 0;
	char separator = 0;
	in >> year >> separator >> month;
	if (year < 1900)
		year = 1900;
	if (year > 3000)
		year = 3000;
	if (month < 1)
		month = 1;
	if (month > 12)
		month = 12;
	
	std::ostringstream out;
	out << year << "-" << month << "-1";
	beginningOfMonth = out.str();
	out.str("");
	
	const char* months[] =
	{
		"",
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};
	
	out << months[month] << " " << year;
	label = out.str();
	out.str("");
	
	if (month == 1)
		out << (year - 1) << "-12-1";
	else
		out << year << "-" << (month - 1) << "-1";
	previousMonth = out.str();
	out.str("");
	
	if (month == 12)
		out << (year + 1) << "-1-1";
	else
		out << year << "-" << (month + 1) << "-1";
	nextMonth = out.str();
}

const std::string& MonthModel::GetBeginningOfMonth() const
{
	return beginningOfMonth;
}

const std::string& MonthModel::GetLabel() const
{
	return label;
}

const std::string& MonthModel::GetPreviousMonth() const
{
	return previousMonth;
}

const std::string& MonthModel::GetNextMonth() const
{
	return nextMonth;
}

