#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HtmlUtility.h"
#include <iostream>
#include <sstream>

std::string GenerateHtmlPage(const std::string& body)
{
	std::ostringstream out;
	out << "<!DOCTYPE html>";
	out << "<html lang=\"en\"><head><title>CGI</title>";
	out << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
	out << "<meta name=\"author\" content=\"Jacob Buysse\">";
	out << "<meta name=\"description\" content=\"Sheepshead Scores\">";
	out << "<link href=\"//netdna.bootstrapcdn.com/bootstrap/3.0.3/css/bootstrap.min.css\" rel=\"stylesheet\">";
	out << "<link href=\"//netdna.bootstrapcdn.com/font-awesome/4.0.1/css/font-awesome.min.css\" rel=\"stylesheet\">";
	out << "</head><body><div class=\"container\">";
	out << body;
	out << "</div>";
	out << "<script src=\"//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js\"></script>";
	out << "<script src=\"//netdna.bootstrapcdn.com/bootstrap/3.0.3/js/bootstrap.min.js\"></script>";
	out << "<script src=\"//ajax.googleapis.com/ajax/libs/angularjs/1.2.4/angular.min.js\"></script>";
	out << "</body></html>";
	return out.str();
}

std::string GeneratePlayer(int number)
{
	std::ostringstream out;
	out << "<div class=\"form-group\">"
		<< "<div class=\"col-sm-3\">"
		<< "<input type=\"text\" class=\"form-control\" name=\"player" << number << "Name\" placeholder=\"Name\">"
		<< "</div>"
		<< "<div class=\"col-sm-2\">"
		<< "<input type=\"number\" class=\"form-control\" name=\"player" << number << "Score\" placeholder=\"Score\">"
		<< "</div>"
		<< "</div>";
	return out.str();
}

HttpResponse DoGet(const HttpRequest& request)
{
	std::ostringstream out;
	out << "<div class=\"jumbotron\">";
	
	out << "<h1>Sheepshead Scores</h1>";
	out << "<p>Enter today's Sheepshead scores and get daily, MTD, and YTD totals.</p>";
	
	out << "<form class=\"form-horizontal\" role=\"form\" action=\"" << request.GetScriptName() << "\" method=\"post\">";
	for (auto number = 1; number <= 6; ++number)
		out << GeneratePlayer(number);
	out << "<div class=\"form-group\">"
		<< "<div class=\"col-sm-2\">"
		<< "<button type=\"submit\" class=\"btn btn-default btn-primary\">Submit</button>"
		<< "</div>"
		<< "<div class=\"col-sm-3\">"
		<< "<p class=\"form-control-static\" style=\"text-align: right;\">P.S. <span>10</span></p>"
		<< "</div>"
		<< "</div>"
		<< "</form>";
		
	out << "</div>";
	
	return { "text/html", GenerateHtmlPage(out.str()) };
}

HttpResponse DoPost(const HttpRequest& request)
{
	std::ostringstream out;
	out << "<h1>Form Post Parameters</h1>";
	
	for (auto queryParameter : request.GetPostData())
	{
		out << "<p>" << Html::EscapeHtml(queryParameter.first) << " = { ";
		for (auto value : queryParameter.second)
			out << "'" << Html::EscapeHtml(value) << "', ";
		out << "}</p>";
	}
	
	return { "text/html", GenerateHtmlPage(out.str()) };
}

HttpResponse DispatchRequest(const HttpRequest& request)
{
	switch (request.GetRequestMethod())
	{
	case HttpRequestMethod::Get:
		return DoGet(request);
		
	case HttpRequestMethod::Post:
		return DoPost(request);
	}
	return { "text/html", GenerateHtmlPage("<p>HTTP request method not supported.</p>") };
}

int main(int argc, char** argv)
{
	HttpRequest request;
	std::cout << DispatchRequest(request);
	return 0;
}

