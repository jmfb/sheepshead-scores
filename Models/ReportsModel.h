#pragma once
#include "ViewType.h"
#include "ReportModel.h"
#include "JsonUtility.h"
#include <vector>

class ReportsModel : public Json::IWriter
{
public:
	ReportsModel();
	ReportsModel(const ReportsModel& rhs) = default;
	~ReportsModel() = default;
	
	ReportsModel& operator=(const ReportsModel& rhs) = default;

	void SetViewType(ViewType value);
	void SetInfiniteScroll(bool value);
	void SetNavigationHtml(const std::string& value);
	void AddReport(const ReportModel& value);
	
	ViewType GetViewType() const;
	bool InfiniteScroll() const;
	const std::string& GetNavigationHtml() const;
	const std::vector<ReportModel>& GetReports() const;

	std::string ToJson() const;

private:
	ViewType viewType;
	bool infiniteScroll;
	std::string navigationHtml;
	std::vector<ReportModel> reports;
};

