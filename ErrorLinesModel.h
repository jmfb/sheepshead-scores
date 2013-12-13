#pragma once
#include <vector>
#include <string>

class ErrorLinesModel
{
public:
	ErrorLinesModel() = default;
	ErrorLinesModel(const ErrorLinesModel& rhs) = default;
	~ErrorLinesModel() = default;
	
	ErrorLinesModel& operator=(const ErrorLinesModel& rhs) = default;
	
	void AddErrorLine(const std::string& value);
	const std::vector<std::string>& GetErrorLines() const;

private:
	std::vector<std::string> errorLines;
};

