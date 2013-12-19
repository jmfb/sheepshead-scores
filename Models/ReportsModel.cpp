#include "ReportsModel.h"

ReportsModel::ReportsModel()
	: infiniteScroll(false)
{
}

void ReportsModel::SetViewType(ViewType value)
{
	viewType = value;
}

void ReportsModel::SetInfiniteScroll(bool value)
{
	infiniteScroll = value;
}

void ReportsModel::SetNavigationHtml(const std::string& value)
{
	navigationHtml = value;
}

void ReportsModel::AddReport(const ReportModel& value)
{
	reports.push_back(value);
}

ViewType ReportsModel::GetViewType() const
{
	return viewType;
}

bool ReportsModel::InfiniteScroll() const
{
	return infiniteScroll;
}

const std::string& ReportsModel::GetNavigationHtml() const
{
	return navigationHtml;
}

const std::vector<ReportModel>& ReportsModel::GetReports() const
{
	return reports;
}

std::string ReportsModel::ToJson() const
{
	return Json::Jsonify("reports", reports);
}

