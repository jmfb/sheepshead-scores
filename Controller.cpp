#include "Controller.h"
#include "PlayerScoreModel.h"
#include "ReportsModel.h"
#include "SubmitScoresView.h"
#include "ReportsView.h"
#include "DataBridge.h"
#include "JsonUtility.h"
#include "DateUtility.h"

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
			return Index();
	
		case HttpRequestMethod::Post:
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
	reports.AddReportLink({ "", "/sheepshead.cgi?action=report-mtd", "MTD Scores" });
	reports.AddReportLink({ "", "/sheepshead.cgi?action=report-ytd", "YTD Scores" });
	reports.AddReportLink({ "", "/sheepshead.cgi?action=report-history", "History" });
	reports.AddReportLink({ "active", "#", "Results" });
	DataBridge dataBridge;
	reports.AddReport(dataBridge.ReportScores(Date::GetToday(), playerScores));
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfMonth(), "MTD Totals"));
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfYear(), "YTD Totals"));
	return View<ReportsView>(reports);
}

HttpResponse Controller::ReportMTD()
{
	ReportsModel reports;
	reports.AddReportLink({ "active", "#", "MTD Scores" });
	reports.AddReportLink({ "", "/sheepshead.cgi?action=report-ytd", "YTD Scores" });
	reports.AddReportLink({ "", "/sheepshead.cgi?action=report-history", "History" });
	DataBridge dataBridge;
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfMonth(), "MTD Totals"));
	return View<ReportsView>(reports);
}

HttpResponse Controller::ReportYTD()
{
	ReportsModel reports;
	reports.AddReportLink({ "", "/sheepshead.cgi?action=report-mtd", "MTD Scores" });
	reports.AddReportLink({ "active", "#", "YTD Scores" });
	reports.AddReportLink({ "", "/sheepshead.cgi?action=report-history", "History" });
	DataBridge dataBridge;
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfYear(), "YTD Totals"));
	return View<ReportsView>(reports);
}

HttpResponse Controller::ReportHistory()
{
	DataBridge dataBridge;
	auto reports = dataBridge.FindGames(0, 10);
	reports.AddReportLink({ "", "/sheepshead.cgi?action=report-mtd", "MTD Scores" });
	reports.AddReportLink({ "", "/sheepshead.cgi?action=report-ytd", "YTD Scores" });
	reports.AddReportLink({ "active", "#", "History" });
	return View<ReportsView>(reports);
}

