#include "YearModel.h"
#include <sstream>

YearModel::YearModel(const std::string& date)
{
	std::istringstream in(date);
	int year = 0;
	in >> year;
	if (year < 1900)
		year = 1900;
	if (year > 3000)
		year = 3000;
	
	std::ostringstream out;
	out << year << "-1-1";
	beginningOfYear = out.str();
	out.str("");
	
	out << year;
	label = out.str();
	out.str("");
	
	out << (year - 1) << "-1-1";
	previousYear = out.str();
	out.str("");
	
	out << (year + 1) << "-1-1";
	nextYear = out.str();
}

const std::string& YearModel::GetBeginningOfYear() const
{
	return beginningOfYear;
}

const std::string& YearModel::GetLabel() const
{
	return label;
}

const std::string& YearModel::GetPreviousYear() const
{
	return previousYear;
}

const std::string& YearModel::GetNextYear() const
{
	return nextYear;
}

