#pragma once
#include <string>

class YearModel
{
public:
	YearModel() = default;
	YearModel(const std::string& date);
	YearModel(const YearModel& rhs) = default;
	~YearModel() = default;
	
	YearModel& operator=(const YearModel& rhs) = default;
	
	const std::string& GetBeginningOfYear() const;
	const std::string& GetLabel() const;
	const std::string& GetPreviousYear() const;
	const std::string& GetNextYear() const;

private:
	std::string beginningOfYear;
	std::string label;
	std::string previousYear;
	std::string nextYear;
};

