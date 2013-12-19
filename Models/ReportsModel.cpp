#include "ReportsModel.h"

void ReportsModel::SetViewType(ViewType value)
{
	viewType = value;
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

const std::string& ReportsModel::GetNavigationHtml() const
{
	return navigationHtml;
}

const std::vector<ReportModel>& ReportsModel::GetReports() const
{
	return reports;
}

