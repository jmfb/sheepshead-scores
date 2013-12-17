#pragma once
#include "ViewType.h"
#include <string>
#include <vector>

class HeaderLink
{
public:
	HeaderLink() = default;
	HeaderLink(
		ViewType viewType,
		const std::string& linkHref,
		const std::string& linkLabel);
	HeaderLink(const HeaderLink& rhs) = default;
	~HeaderLink() = default;
	
	HeaderLink& operator=(const HeaderLink& rhs) = default;
	
	ViewType GetViewType() const;
	const std::string& GetLinkClass(ViewType currentView) const;
	const std::string& GetLinkHref(ViewType currentView) const;
	const std::string& GetLinkLabel() const;
	
private:
	ViewType viewType;
	std::string linkHref;
	std::string linkLabel;
};

std::vector<HeaderLink> GetHeaderLinks();

