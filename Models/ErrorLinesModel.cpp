#include "ErrorLinesModel.h"

void ErrorLinesModel::AddErrorLine(const std::string& value)
{
	errorLines.push_back(value);
}

const std::vector<std::string>& ErrorLinesModel::GetErrorLines() const
{
	return errorLines;
}

