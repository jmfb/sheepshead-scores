#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HtmlUtility.h"
#include "StringUtility.h"
#include "JsonUtility.h"
#include "DateUtility.h"
#include "PlayerScore.h"
#include <iostream>
#include <sstream>
#include <pqxx/pqxx>
#include <ctime>

//sudo -u postgres createuser "www-data"
//sudo apt-get install libpqxx-3.1
//sudo apt-get install libpqxx3-dev

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

	pqxx::connection connection("dbname=sheepshead");
	pqxx::work transaction(connection);
	auto result = transaction.exec("select name from player where name like " + transaction.quote("%" + query + "%") + " order by name limit 5;");

	std::ostringstream out;
	out << "{\"names\":[";
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		if (iter != result.begin())
			out << ",";
		out << "\"" << Json::EscapeJson((*iter)[0].as<std::string>()) << "\"";
	}
	out << "]}";
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

std::string ReportScoresSince(pqxx::work& transaction, const std::string& since, const char* title)
{
	auto results = transaction.exec("select player.name, sum(gamePlayer.score) from game inner join gamePlayer on gamePlayer.gameId = game.id inner join player on player.id = gamePlayer.playerId where game.playedWhen >= " + transaction.quote(since) + " group by player.name order by 2 desc;");
	std::ostringstream out;
	out << "<div class=\"well\">"
		<< "<h1>" << Html::EscapeHtml(title) << "</h1>"
		<< "<table class=\"table table-striped\">"
		<< "<thead><tr><th>Player</th><th>Score</th></tr></thead>"
		<< "<tbody>";
	auto pointSpread = 0;
	auto playerScores = PlayerScore::LoadAll(results, 0, 1);
	
	for (auto playerScore : playerScores)
	{
		auto score = playerScore.GetScore();
		if (score > 0)
			pointSpread += score;
		out << "<tr><td>" << Html::EscapeHtml(playerScore.GetName()) << "</td>"
			<< "<td>" << score << "</td></tr>";
	}
		
	out << "</tbody>"
		<< "<tfoot><tr class=\"success\"><td>P.S.</td><td>" << pointSpread << "</td></tr></tfoot>"
		<< "</table>"
		<< "</div>";

	return out.str();
}

HttpResponse DoPost(const HttpRequest& request)
{
	pqxx::connection connection("dbname=sheepshead");
	pqxx::work transaction(connection);

	auto today = Date::GetToday();
	auto result = transaction.exec("select id from game where playedwhen = " + transaction.quote(today) + ";");
	if (result.empty())
		result = transaction.exec("insert into game (playedwhen) values (" + transaction.quote(today) + ") returning id;");
	
	auto gameId = result[0][0].as<int>();

	std::ostringstream out;
	out << "<div class=\"row\"><div class=\"col-md-offset-2 col-md-8\">";
	out << "<div class=\"well\">";
	out << "<h1>New Scores for " << today << ".</h1>";
	out << "<table class=\"table table-striped\">"
		<< "<thead><tr><th>Player</th><th>Score</th></tr></thead>"
		<< "<tbody>";
	
	auto pointSpread = 0;
	auto playerScores = PlayerScore::LoadAll(request.GetPostData());
	for (auto playerScore : playerScores)
	{
		auto name = playerScore.GetName();
		result = transaction.exec("select id from player where name = " + transaction.quote(name) + ";");
		if (result.empty())
			result = transaction.exec("insert into player (name) values (" + transaction.quote(name) + ") returning id;");
			
		auto playerId = result[0][0].as<int>();
		
		auto score = playerScore.GetScore();
		if (score > 0)
			pointSpread += score;
		out << "<tr><td>" << Html::EscapeHtml(name) << "</td><td>" << score << "</td></tr>";
		
		result = transaction.exec("select score from gamePlayer where gameId = " + transaction.quote(gameId) + " and playerId = " + transaction.quote(playerId) + ";");
		if (result.empty())
			transaction.exec("insert into gamePlayer (gameId, playerId, score) values (" + transaction.quote(gameId) + ", " + transaction.quote(playerId) + ", " + transaction.quote(score) + ");");
		else
			transaction.exec("update gamePlayer set score = " + transaction.quote(score + result[0][0].as<int>()) + " where gameId = " + transaction.quote(gameId) + " and playerId = " + transaction.quote(playerId) + ";");
	}
	
	out << "</tbody>"
		<< "<tfoot><tr class=\"success\"><td>P.S.</td><td>" << pointSpread << "</td></tr></tfoot>"
		<< "</table>"
		<< "</div>";
	
	out << ReportScoresSince(transaction, Date::GetBeginningOfMonth(), "MTD Totals");
	out << ReportScoresSince(transaction, Date::GetBeginningOfYear(), "YTD Totals");

	out << "</div></div>";
		
	transaction.commit();
	
	return { "text/html", GenerateHtmlPage("Sheepshead Results", out.str()) };
}

HttpResponse DispatchRequest(const HttpRequest& request)
{
	try
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
	catch (const std::exception& exception)
	{
		return { "text/html", GenerateHtmlPage("Error", "<pre>" + String::Replace(Html::EscapeHtml(exception.what()), "\n", "<br/>") + "</pre>"), 500 };
	}
}

int main(int argc, char** argv)
{
	HttpRequest request;
	std::cout << DispatchRequest(request);
	return 0;
}

