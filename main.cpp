#include "QueryString.h"
#include "HtmlUtility.h"
#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "Content-type: text/html" << std::endl << std::endl;
	std::cout << "<html><head><title>CGI</title></head><body>";
	
	std::cout << "<h1>Query String Parameters</h1>";
	
	QueryString queryString;
	for (auto queryParameter : queryString)
	{
		std::cout << "<p>" << Html::EscapeHtml(queryParameter.first) << " = { ";
		for (auto value : queryParameter.second)
			std::cout << "'" << Html::EscapeHtml(value) << "', ";
		std::cout << "}</p>";
	}
	
	std::cout << "</body></html>";
	return 0;
}

