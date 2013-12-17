#include "BaseController.h"
#include "ErrorLinesModel.h"
#include "ErrorView.h"
#include <sstream>
#include <iostream>
#include <string>

HttpResponse BaseController::Error(const std::string& error, int statusCode)
{
	ErrorLinesModel errorLines;
	std::istringstream in(error);
	std::string errorLine;
	while (std::getline(in, errorLine))
		errorLines.AddErrorLine(errorLine);
	return View<ErrorView>(errorLines, statusCode);
}

HttpResponse BaseController::Redirect(const std::string& location)
{
	return { location };
}

