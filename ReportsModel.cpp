#include "ReportsModel.h"

void ReportsModel::AddReportLink(const ReportLinkModel& value)
{
	reportLinks.push_back(value);
}

void ReportsModel::AddReport(const ReportModel& value)
{
	reports.push_back(value);
}

const std::vector<ReportLinkModel>& ReportsModel::GetReportLinks() const
{
	return reportLinks;
}

const std::vector<ReportModel>& ReportsModel::GetReports() const
{
	return reports;
}

