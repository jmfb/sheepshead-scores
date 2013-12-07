#include "QueryString.h"
#include "PostData.h"
#include "HtmlUtility.h"
#include <iostream>

#include <cstring>

enum class HttpRequestMethod { Get, Post, Other };

HttpRequestMethod GetRequestMethod()
{
	auto value = std::getenv("REQUEST_METHOD");
	if (value == nullptr)
		return HttpRequestMethod::Other;
	if (std::strcmp(value, "GET") == 0)
		return HttpRequestMethod::Get;
	if (std::strcmp(value, "POST") == 0)
		return HttpRequestMethod::Post;
	return HttpRequestMethod::Other;
}

void DoGet();
void DoPost();

int main(int argc, char** argv)
{
	std::cout << "Content-type: text/html" << std::endl << std::endl;
	std::cout << "<!DOCTYPE html>";
	std::cout << "<html><head><title>CGI</title>";
	std::cout << "<meta name=\"display\" content=\"width=device-width, initial-scale=1.0\">";
	std::cout << "<meta name=\"author\" content=\"Jacob Buysse\">";
	std::cout << "<meta name=\"description\" content=\"Sheepshead Scores\">";
	std::cout << "<link href=\"//netdna.bootstrapcdn.com/bootstrap/3.0.3/css/bootstrap.min.css\" rel=\"stylesheet\">";
	std::cout << "<link href=\"//netdna.bootstrapcdn.com/font-awesome/4.0.1/css/font-awesome.min.css\" rel=\"stylesheet\">";
	std::cout << "</head><body>";
	
	switch (GetRequestMethod())
	{
	case HttpRequestMethod::Get:
		DoGet();
		break;
		
	case HttpRequestMethod::Post:
		DoPost();
		break;
	
	default:
		std::cout << "<p>HTTP request method not supported.</p>";
		break;
	}
	
	std::cout << "<script src=\"//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js\"></script>";
	std::cout << "<script src=\"//netdna.bootstrapcdn.com/bootstrap/3.0.3/js/bootstrap.min.js\"></script>";
	std::cout << "<script src=\"//ajax.googleapis.com/ajax/libs/angularjs/1.2.4/angular.min.js\"></script>";
	std::cout << "</body></html>";
	return 0;
}

std::string GetScriptName()
{
	auto value = std::getenv("SCRIPT_NAME");
	return value == nullptr ? "" : value;
}

void DoGet()
{
	std::cout << "<h1>Post Sheepshead Scores</h1>";
	
	std::cout << "<form action=\"" << GetScriptName() << "\" method=\"post\">"
		<< "Name: <input type=\"text\" name=\"name\">"
		<< "Score: <input type=\"text\" name=\"score\">"
		<< "<button type=\"submit\">Submit</button>"
		<< "</form>";

	std::cout << "<h1>Query String Parameters</h1>";
	
	QueryString queryString;
	for (auto queryParameter : queryString)
	{
		std::cout << "<p>" << Html::EscapeHtml(queryParameter.first) << " = { ";
		for (auto value : queryParameter.second)
			std::cout << "'" << Html::EscapeHtml(value) << "', ";
		std::cout << "}</p>";
	}
}

void DoPost()
{
	std::cout << "<h1>Form Post Parameters</h1>";
	
	PostData postData;
	for (auto queryParameter : postData)
	{
		std::cout << "<p>" << Html::EscapeHtml(queryParameter.first) << " = { ";
		for (auto value : queryParameter.second)
			std::cout << "'" << Html::EscapeHtml(value) << "', ";
		std::cout << "}</p>";
	}
}

