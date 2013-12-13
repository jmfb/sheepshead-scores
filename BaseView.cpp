#include "BaseView.h"

std::string BaseView::Render()
{
	content.str("");
	RenderBody();
	return content.str();
}

void BaseView::RenderBody()
{
}

void BaseView::Write(const std::string& value)
{
	content << value;
}

