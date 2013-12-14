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
			if (request.GetQueryString()("action") == "name-lookup")
				return LookupNames(request.GetQueryString()("query"));
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
	DataBridge dataBridge;
	reports.AddReport(dataBridge.ReportScores(Date::GetToday(), playerScores));
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfMonth(), "MTD Totals"));
	reports.AddReport(dataBridge.ReportScoresSince(Date::GetBeginningOfYear(), "YTD Totals"));
	return View<ReportsView>(reports);
}

