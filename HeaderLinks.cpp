#include "HeaderLinks.h"

HeaderLink::HeaderLink(
	ViewType viewType,
	const std::string& linkHref,
	const std::string& linkLabel)
	: viewType(viewType), linkHref(linkHref), linkLabel(linkLabel)
{
}

ViewType HeaderLink::GetViewType() const
{
	return viewType;
}

const std::string& HeaderLink::GetLinkClass(ViewType currentView) const
{
	static const std::string currentLinkClass = "active";
	static const std::string defaultLinkClass = "";
	return currentView == viewType ? currentLinkClass : defaultLinkClass;
}

const std::string& HeaderLink::GetLinkHref(ViewType currentView) const
{
	static const std::string currentLinkHref = "#";
	return currentView == viewType ? currentLinkHref : linkHref;
}

const std::string& HeaderLink::GetLinkLabel() const
{
	return linkLabel;
}

std::vector<HeaderLink> GetHeaderLinks()
{
	return
	{
		{ ViewType::SubmitScores, "/sheepshead.cgi", "Home" },
		{ ViewType::UploadScores, "/sheepshead.cgi?action=upload-scores", "Upload" },
		{ ViewType::ReportMTD, "/sheepshead.cgi?action=report-mtd", "MTD Scores" },
		{ ViewType::ReportYTD, "/sheepshead.cgi?action=report-ytd", "YTD Scores" },
		{ ViewType::ReportHistory, "/sheepshead.cgi?action=report-history", "History" }
	};
}

