#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HtmlUtility.h"
#include <iostream>
#include <sstream>

std::string GenerateHtmlPage(const std::string& title, const std::string& body)
{
	std::ostringstream out;
	out << "<!DOCTYPE html>";
	out << "<html lang=\"en\" ng-app=\"sheepsheadApp\"><head>";
	out << "<meta charset=\"utf-8\">";
	out << "<title>" << title << "</title>";
	out << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
	out << "<meta name=\"author\" content=\"Jacob Buysse\">";
	out << "<meta name=\"description\" content=\"Sheepshead Scores\">";
	out << "<link href=\"//netdna.bootstrapcdn.com/bootstrap/3.0.3/css/bootstrap.min.css\" rel=\"stylesheet\">";
	out << "<link href=\"//netdna.bootstrapcdn.com/font-awesome/4.0.1/css/font-awesome.min.css\" rel=\"stylesheet\">";
	out << "<link href=\"//code.jquery.com/ui/1.10.3/themes/smoothness/jquery-ui.css\" rel=\"stylesheet\">";
	out << "<link href=\"styles.css\" rel=\"stylesheet\">";
	out << "<script src=\"//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js\"></script>";
	out << "<script src=\"//ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/jquery-ui.min.js\"></script>";
	out << "<script src=\"//netdna.bootstrapcdn.com/bootstrap/3.0.3/js/bootstrap.min.js\"></script>";
	out << "<script src=\"//ajax.googleapis.com/ajax/libs/angularjs/1.2.4/angular.min.js\"></script>";
	out << "<script src=\"controllers.js\"></script>";
	out << "</head><body ng-controller=\"SheepsheadScoreCtrl\"><div class=\"container\">";
	out << body;
	out << "</div>";
	out << "<script src=\"initialize.js\"></script>";
	out << "</body></html>";
	return out.str();
}

std::string GeneratePlayer(int number)
{
	std::ostringstream out;
	out << "<div class=\"form-group\">"
		<< "<div class=\"col-sm-3\">"
		<< "<input type=\"text\" class=\"form-control name-lookup\" name=\"player" << number << "Name\" placeholder=\"Name\" ng-model=\"player" << number << "Name\" autocomplete=\"off\">"
		<< "</div>"
		<< "<div class=\"col-sm-2\">"
		<< "<input type=\"number\" class=\"form-control\" name=\"player" << number << "Score\" placeholder=\"Score\" ng-model=\"player" << number << "Score\">"
		<< "</div>"
		<< "</div>";
	return out.str();
}

bool IsNameLookup(const HttpRequest& request)
{
	auto values = request.GetQueryString()["action"];
	return values.size() == 1 && values[0] == "name-lookup";
}

HttpResponse DoNameLookup(const HttpRequest& request)
{
	auto values = request.GetQueryString()["query"];
	auto query = values.empty() ? "" : values[0];
	std::ostringstream out;
	out << "{ \"names\": [ ";
	out << "\"" << query << 0 << "\"";
	for (auto index = 1; index < 5; ++index)
		out << ", \"" << query << index << "\"";
	out << " ] }";
	return { "application/json", out.str() };
}

HttpResponse DoGet(const HttpRequest& request)
{
	if (IsNameLookup(request))
		return DoNameLookup(request);

	std::ostringstream out;
	out << "<div class=\"jumbotron\">";
	
	out << "<h2>Sheepshead Scores</h2>";
	out << "<p>Enter today's Sheepshead scores and get daily, MTD, and YTD totals.</p>";
	
	out << "<form class=\"form-horizontal\" role=\"form\" action=\"" << request.GetScriptName() << "\" method=\"post\">";
	for (auto number = 1; number <= 6; ++number)
		out << GeneratePlayer(number);
	out << "<div class=\"form-group\">"
		<< "<div class=\"col-sm-2\">"
		<< "<button type=\"submit\" class=\"btn btn-default btn-primary\" ng-disabled=\"!isValid()\">Submit</button>"
		<< "</div>"
		<< "<div class=\"col-sm-3\">"
		<< "<p class=\"form-control-static\" style=\"text-align: right;\">P.S. <span>{{getPositivePointSpread()}}</span></p>"
		<< "</div>"
		<< "</div>"
		<< "</form>";
		
	out << "<div ng-show=\"getCheckSum()\" class=\"alert alert-danger\">Checksum is {{getCheckSum()}} instead of 0.</div>";
		
	out << "</div>";
	
	return { "text/html", GenerateHtmlPage("Sheepshead Scores", out.str()) };
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
	
	return { "text/html", GenerateHtmlPage("Sheepshead Results", out.str()) };
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
	return { "text/html", GenerateHtmlPage("Error", "<p>HTTP request method not supported.</p>") };
}

int main(int argc, char** argv)
{
	HttpRequest request;
	std::cout << DispatchRequest(request);
	return 0;
}

//sudo apt-get install libpqxx-3.1
//sudo apt-get install libpqxx3-dev
//g++ -std=c++0x *.cpp -lpqxx -lpq -o test
/*
#include <pqxx/pqxx>

void foo()
{
	pqxx::connection connection("dbname=sheepshead");
	if (connection.is_open())
	{
		std::cout << "success" << std::endl;	
	}
	else
	{
		std::cout << "could not connect." << std::endl;
	}
}
*/

