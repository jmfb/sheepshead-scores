#pragma once
#include <string>

class MonthModel
{
public:
	MonthModel() = default;
	MonthModel(const std::string& date);
	MonthModel(const MonthModel& rhs) = default;
	~MonthModel() = default;
	
	MonthModel& operator=(const MonthModel& rhs) = default;
	
	const std::string& GetBeginningOfMonth() const;
	const std::string& GetLabel() const;
	const std::string& GetPreviousMonth() const;
	const std::string& GetNextMonth() const;
	
private:
	std::string beginningOfMonth;
	std::string label;
	std::string previousMonth;
	std::string nextMonth;
};

