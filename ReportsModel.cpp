#include "ReportsModel.h"

void ReportsModel::AddReport(const ReportModel& value)
{
	reports.push_back(value);
}

const std::vector<ReportModel>& ReportsModel::GetReports() const
{
	return reports;
}

