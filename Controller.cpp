#include "Controller.h"
#include "PlayerScoreModel.h"
#include "ReportsModel.h"
#include "SubmitScoresView.h"
#include "ReportsView.h"
#include "UploadScoresView.h"
#include "DataBridge.h"
#include "JsonUtility.h"
#include "DateUtility.h"
#include "StringUtility.h"

HttpResponse Controller::Execute()
{
	try
	{
		switch (request.GetRequestMethod())
		{
		case HttpRequestMethod::Get:
			if (IsAction("name-lookup"))
				return LookupNames(request.GetQueryString()("query"));
			else if (IsAction("report-mtd"))
				return ReportMTD();
			else if (IsAction("report-ytd"))
				return ReportYTD();
			else if (IsAction("report-history"))
				return ReportHistory();
			else if (IsAction("upload-scores"))
				return UploadScores();
			return Index();
	
		case HttpRequestMethod::Post:
			if (IsAction("upload-scores"))
				return UploadScores({});
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
	return request.GetQueryString()("action") == name;
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
	reports.AddReport(dataBridge.ReportScores(Date::GetToday(), playerScores));
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfMonth(), "MTD Totals"));
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfYear(), "YTD Totals"));
	return View<ReportsView>(reports);
}

HttpResponse Controller::ReportMTD()
{
	ReportsModel reports;
	reports.SetViewType(ViewType::ReportMTD);
	DataBridge dataBridge;
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfMonth(), "MTD Totals"));
	return View<ReportsView>(reports);
}

HttpResponse Controller::ReportYTD()
{
	ReportsModel reports;
	reports.SetViewType(ViewType::ReportYTD);
	DataBridge dataBridge;
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfYear(), "YTD Totals"));
	return View<ReportsView>(reports);
}

HttpResponse Controller::ReportHistory()
{
	DataBridge dataBridge;
	auto reports = dataBridge.FindGames(0, 10);
	reports.SetViewType(ViewType::ReportHistory);
	return View<ReportsView>(reports);
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
	DataBridge dataBridge;
	while (std::getline(in, line))
	{
		if (line.empty())
			continue;
		auto values = String::Split(line, ",");
		if (values.size() != headers.size())
			return Error("Values must match headers.\n" + std::to_string(headers.size()) + " headers, " + std::to_string(values.size()) + " values.\n" + header + "\n" + line, 400);
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
		dataBridge.ReportScores(date, playerScores);
	}
	return View<SubmitScoresView>();
}

