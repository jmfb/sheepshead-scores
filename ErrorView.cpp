#include "ErrorView.h"
#include "HtmlUtility.h"

void ErrorView::RenderBody_Error()
{
}

void ErrorView::RenderBody_Layout()
{
	Write("<pre>");
	Write(" ");
	for (auto errorLine : model.GetErrorLines()) {
	Write(" ");
	Write(Html::EscapeHtml(errorLine));
	Write("<br/>");
	Write(" ");
	}
	Write(" ");
	Write("</pre>");
	Write(" ");
	Write(" ");
}

void ErrorView::RenderSection_Layout_Title()
{
	Write("Error");
	Write(" ");
}

void ErrorView::SetModel(const ErrorLinesModel& value)
{
	model = value;
}

