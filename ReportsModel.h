#pragma once
#include "ViewType.h"
#include "ReportModel.h"
#include <vector>

class ReportsModel
{
public:
	ReportsModel() = default;
	ReportsModel(const ReportsModel& rhs) = default;
	~ReportsModel() = default;
	
	ReportsModel& operator=(const ReportsModel& rhs) = default;

	void SetViewType(ViewType value);
	void SetNavigationHtml(const std::string& value);
	void AddReport(const ReportModel& value);
	
	ViewType GetViewType() const;
	const std::string& GetNavigationHtml() const;
	const std::vector<ReportModel>& GetReports() const;

private:
	ViewType viewType;
	std::string navigationHtml;
	std::vector<ReportModel> reports;
};

