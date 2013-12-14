#include "ReportLinkModel.h"

ReportLinkModel::ReportLinkModel(
	const std::string& linkClass,
	const std::string& linkHref,
	const std::string& linkLabel)
	: linkClass(linkClass), linkHref(linkHref), linkLabel(linkLabel)
{
}

const std::string& ReportLinkModel::GetLinkClass() const
{
	return linkClass;
}

const std::string& ReportLinkModel::GetLinkHref() const
{
	return linkHref;
}

const std::string& ReportLinkModel::GetLinkLabel() const
{
	return linkLabel;
}

