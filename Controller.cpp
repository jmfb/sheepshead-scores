#include "Controller.h"
#include "ReportsModel.h"
#include "SubmitScoresView.h"
#include "ReportsView.h"
#include "UploadScoresView.h"
#include "MonthNavigationView.h"
#include "YearNavigationView.h"
#include "PlayerGamesView.h"
#include "DataBridge.h"
#include "JsonUtility.h"
#include "DateUtility.h"
#include "StringUtility.h"
#include "Debug.h"
#include "HttpContext.h"

HttpResponse Controller::Execute()
{
	auto response = InternalExecute();
	if (Debug::GetInstance().HasMessages())
		return { "application/json", Json::Jsonify("messages", Debug::GetInstance().GetMessages()) };
	return response;
}

HttpResponse Controller::InternalExecute()
{
	try
	{
		switch (request.GetRequestMethod())
		{
		case HttpRequestMethod::Get:
			if (IsAction("name-lookup"))
				return LookupNames(request.GetQueryString()("query"));
			else if (IsAction("report-mtd"))
				return ReportMTD(request.GetQueryString()("date"));
			else if (IsAction("report-ytd"))
				return ReportYTD(request.GetQueryString()("date"));
			else if (IsAction("report-history"))
				return ReportHistory();
			else if (IsAction("load-history"))
				return LoadHistory(std::stoi(request.GetQueryString()("skip")));
			else if (IsAction("report-player"))
				return ReportPlayer(
					request.GetQueryString()("player"),
					request.GetQueryString()("date"));
			else if (IsAction("upload-scores"))
				return UploadScores();
			return Index();
	
		case HttpRequestMethod::Post:
			if (IsAction("upload-scores"))
				return UploadScores({});
			else if (IsAction("delete-game"))
				return DeleteGame(std::stoi(request.GetPostData()("gameId")));
			else if (IsAction("submit-hands"))
				return SubmitHands({ request.GetJsonData().GetJson() });
			else if (IsAction("get-games-by-date-for-players"))
				return GetGamesByDateForPlayers({ request.GetJsonData().GetJson() });
			else if (IsAction("get-scores-by-date"))
				return GetScoresByDate(request.GetJsonData().GetJson()["period"].asString());
			return SubmitScores(PlayerScoreModel::LoadAll(request.GetPostData()));
		}
		return Error("HTTP request method not supported.", 400);
	}
	catch (const std::exception& exception)
	{
		return Error(exception.what(), 500);
	}
}

bool Controller::IsAction(const std::string& name) const
{
	return request.GetQueryString()("action") == name ||
		request.GetPostData()("action") == name;
}

HttpResponse Controller::Index()
{
	return View<SubmitScoresView>();
}

HttpResponse Controller::LookupNames(const std::string& query)
{
	DataBridge dataBridge;
	auto model = dataBridge.LookupNames(query);
	return Json::Content(model);
}

HttpResponse Controller::SubmitScores(const std::vector<PlayerScoreModel>& playerScores)
{
	ReportsModel reports;
	reports.SetViewType(ViewType::Summary);
	DataBridge dataBridge;
	auto today = Date::GetToday();
	reports.AddReport(dataBridge.ReportScores(today, playerScores));
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfMonth(), "3000-01-01", "MTD Totals"));
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfYear(), "3000-01-01", "YTD Totals"));
	return View<ReportsView>(reports);
}

HttpResponse Controller::SubmitHands(const HandsModel& handsModel)
{
	ReportsModel reports;
	reports.SetViewType(ViewType::Summary);
	DataBridge dataBridge;
	auto today = Date::GetToday();
	auto gameReport = dataBridge.ReportHands(today, handsModel.GetPlayerNames(), handsModel.GetHands());
	reports.AddReport(gameReport);
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfMonth(), "3000-01-01", "MTD Totals"));
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfYear(), "3000-01-01", "YTD Totals"));
	return View<ReportsView>(reports);
}

HttpResponse Controller::ReportMTD(const std::string& requestedDate)
{
	auto date = requestedDate.empty() ? Date::GetBeginningOfMonth() : requestedDate;
	MonthModel model(date);
	ReportsModel reports;
	reports.SetViewType(ViewType::ReportMTD);
	reports.SetNavigationHtml(Partial<MonthNavigationView>(model));
	DataBridge dataBridge;
	auto title = "MTD Totals - " + model.GetLabel();
	reports.AddReport(dataBridge.ReportScoresSince(model.GetBeginningOfMonth(), model.GetNextMonth(), title));
	return View<ReportsView>(reports);
}

HttpResponse Controller::ReportYTD(const std::string& requestedDate)
{
	auto date = requestedDate.empty() ? Date::GetBeginningOfYear() : requestedDate;
	YearModel model(date);
	ReportsModel reports;
	reports.SetViewType(ViewType::ReportYTD);
	reports.SetNavigationHtml(Partial<YearNavigationView>(model));
	DataBridge dataBridge;
	auto title = "YTD Totals - " + model.GetLabel();
	reports.AddReport(dataBridge.ReportScoresSince(model.GetBeginningOfYear(), model.GetNextYear(), title));
	return View<ReportsView>(reports);
}

HttpResponse Controller::ReportHistory()
{
	DataBridge dataBridge;
	auto reports = dataBridge.FindGames(0, 10);
	reports.SetViewType(ViewType::ReportHistory);
	reports.SetInfiniteScroll(true);
	return View<ReportsView>(reports);
}

HttpResponse Controller::LoadHistory(int skip)
{
	DataBridge dataBridge;
	auto reports = dataBridge.FindGames(skip, 10);
	return Json::Content(reports);
}

HttpResponse Controller::ReportPlayer(const std::string& player, const std::string& date)
{
	PlayerGamesModel model;
	model.SetPlayer(player);
	model.SetDate(date.empty() ? Date::GetBeginningOfYear() : date);
	if (!player.empty())
	{
		DataBridge dataBridge;
		auto games = dataBridge.ReportPlayerGames(player, model.GetBeginningOfYear(), model.GetNextYear());
		for (auto game : games)
			model.AddGame(game);
	}
	return View<PlayerGamesView>(model);
}

HttpResponse Controller::UploadScores()
{
	return View<UploadScoresView>();
}

HttpResponse Controller::UploadScores(const FileUploadData& fileUpload)
{
	std::istringstream in(fileUpload.GetContent());
	std::string header;
	std::getline(in, header);
	std::string line;
	auto headers = String::Split(header, ",");
	if (headers.empty() || headers[0] != "Date")
		return Error("Headers cannot be empty and must have Date in first column.\n" + header, 400);
	std::vector<std::pair<std::string, std::vector<PlayerScoreModel>>> games;
	while (std::getline(in, line))
	{
		if (line.empty())
			continue;
		auto values = String::Split(line, ",");
		if (values.size() != headers.size())
			return Error("Values must match headers.\n" + line, 400);
		auto date = values[0];
		std::vector<PlayerScoreModel> playerScores;
		auto checkSum = 0;
		for (auto index = 1ul; index < values.size(); ++index)
		{
			auto value = values[index];
			if (value.empty())
				continue;
			try
			{
				auto score = std::stoi(value);
				checkSum += score;
				playerScores.push_back({ headers[index], score });
			}
			catch (...)
			{
				return Error("Parse error: (" + value + ")\n" + line, 400);
			}
		}
		
		if (playerScores.size() < 5)
			return Error("Games must contain at least 5 players (" + date + ")", 400);
		if (checkSum != 0)
			return Error("Games must have a check sum of zero (" + date + ")", 400);
		games.push_back({ date, playerScores });
	}

	DataBridge dataBridge;
	for (auto game : games)
		dataBridge.ReportScores(game.first, game.second);

	return Redirect("/sheepshead.cgi");
}

HttpResponse Controller::DeleteGame(int gameId)
{
	DataBridge dataBridge;
	dataBridge.DeleteGame(gameId);
	return Redirect("/sheepshead.cgi");
}

HttpResponse Controller::GetGamesByDateForPlayers(
	const GamesByDateForPlayersRequest& requestModel)
{
	DataBridge dataBridge;
	auto games = dataBridge.GetGamesByDateForPlayers(
		requestModel.GetPlayerNames(),
		requestModel.GetPeriodStart(),
		requestModel.GetPeriodEnd());
	return Json::Content(games);
}

HttpResponse Controller::GetScoresByDate(const std::string& period)
{
	DataBridge dataBridge;
	auto scores = dataBridge.GetScoresByDate(
		Date::GetBeginningOfPeriod(period),
		Date::GetEndOfPeriod(period));
	return Json::Content(scores);
}
