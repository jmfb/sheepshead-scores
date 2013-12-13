#pragma once
#include "ReportModel.h"
#include <vector>

class ReportsModel
{
public:
	ReportsModel() = default;
	ReportsModel(const ReportsModel& rhs) = default;
	~ReportsModel() = default;
	
	ReportsModel& operator=(const ReportsModel& rhs) = default;

	void AddReport(const ReportModel& value);
	const std::vector<ReportModel>& GetReports() const;

private:
	std::vector<ReportModel> reports;
};

