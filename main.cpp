#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HtmlUtility.h"
#include "StringUtility.h"
#include "JsonUtility.h"
#include "DateUtility.h"
#include "PlayerScoreModel.h"
#include "SubmitScoresView.h"
#include "ReportsView.h"
#include "ErrorView.h"
#include <iostream>
#include <sstream>
#include <pqxx/pqxx>
#include <ctime>

//sudo -u postgres createuser "www-data"
//sudo apt-get install libpqxx-3.1
//sudo apt-get install libpqxx3-dev

bool IsNameLookup(const HttpRequest& request)
{
	auto values = request.GetQueryString()["action"];
	return values.size() == 1 && values[0] == "name-lookup";
}

HttpResponse DoNameLookup(const HttpRequest& request)
{
	auto query = request.GetQueryString()("query");

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
	return View<SubmitScoresView>();
}

ReportModel ReportScoresSince(pqxx::work& transaction, const std::string& since, const std::string& title)
{
	auto results = transaction.exec("select player.name, sum(gamePlayer.score) from game inner join gamePlayer on gamePlayer.gameId = game.id inner join player on player.id = gamePlayer.playerId where game.playedWhen >= " + transaction.quote(since) + " group by player.name order by 2 desc, 1 asc;");

	ReportModel report;
	report.SetTitle(title);
	auto playerScores = PlayerScoreModel::LoadAll(results, 0, 1);
	for (auto playerScore : playerScores)
		report.AddPlayerScore(playerScore);
	return report;
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

	ReportModel reportToday;
	reportToday.SetTitle("New Scores for " + today + ".");

	auto playerScores = PlayerScoreModel::LoadAll(request.GetPostData());
	for (auto playerScore : playerScores)
	{
		reportToday.AddPlayerScore(playerScore);
		
		auto name = playerScore.GetName();
		result = transaction.exec("select id from player where name = " + transaction.quote(name) + ";");
		if (result.empty())
			result = transaction.exec("insert into player (name) values (" + transaction.quote(name) + ") returning id;");
			
		auto playerId = result[0][0].as<int>();
		auto score = playerScore.GetScore();
		
		result = transaction.exec("select score from gamePlayer where gameId = " + transaction.quote(gameId) + " and playerId = " + transaction.quote(playerId) + ";");
		if (result.empty())
			transaction.exec("insert into gamePlayer (gameId, playerId, score) values (" + transaction.quote(gameId) + ", " + transaction.quote(playerId) + ", " + transaction.quote(score) + ");");
		else
			transaction.exec("update gamePlayer set score = " + transaction.quote(score + result[0][0].as<int>()) + " where gameId = " + transaction.quote(gameId) + " and playerId = " + transaction.quote(playerId) + ";");
	}

	ReportsModel reports;
	reports.AddReport(reportToday);
	reports.AddReport(ReportScoresSince(transaction, Date::GetBeginningOfMonth(), "MTD Totals"));
	reports.AddReport(ReportScoresSince(transaction, Date::GetBeginningOfYear(), "YTD Totals"));
		
	transaction.commit();
	
	return View<ReportsView>(reports);
}

HttpResponse Error(const std::string& error, int statusCode)
{
	ErrorLinesModel errorLines;
	std::istringstream in(error);
	std::string errorLine;
	while (std::getline(in, errorLine))
		errorLines.AddErrorLine(errorLine);
	return View<ErrorView>(errorLines, statusCode);
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
		return Error("HTTP request method not supported.", 400);
	}
	catch (const std::exception& exception)
	{
		return Error(exception.what(), 500);
	}
}

int main(int argc, char** argv)
{
	HttpRequest request;
	std::cout << DispatchRequest(request);
	return 0;
}

