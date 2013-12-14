#pragma once
#include "ReportLinkModel.h"
#include "ReportModel.h"
#include <vector>

class ReportsModel
{
public:
	ReportsModel() = default;
	ReportsModel(const ReportsModel& rhs) = default;
	~ReportsModel() = default;
	
	ReportsModel& operator=(const ReportsModel& rhs) = default;

	void AddReportLink(const ReportLinkModel& value);
	void AddReport(const ReportModel& value);
	
	const std::vector<ReportLinkModel>& GetReportLinks() const;
	const std::vector<ReportModel>& GetReports() const;

private:
	std::vector<ReportLinkModel> reportLinks;
	std::vector<ReportModel> reports;
};

