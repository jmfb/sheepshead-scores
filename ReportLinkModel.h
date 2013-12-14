#pragma once
#include <string>

class ReportLinkModel
{
public:
	ReportLinkModel() = default;
	ReportLinkModel(
		const std::string& linkClass,
		const std::string& linkHref,
		const std::string& linkLabel);
	ReportLinkModel(const ReportLinkModel& rhs) = default;
	~ReportLinkModel() = default;
	
	ReportLinkModel& operator=(const ReportLinkModel& rhs) = default;

	const std::string& GetLinkClass() const;
	const std::string& GetLinkHref() const;
	const std::string& GetLinkLabel() const;
	
private:
	std::string linkClass;
	std::string linkHref;
	std::string linkLabel;
};

