#include "YearNavigationView.h"
#include "HtmlUtility.h"

void YearNavigationView::RenderBody_YearNavigation()
{
}

void YearNavigationView::RenderBody()
{
	Write("<div style=\"height: 52px;\">");
	Write(" ");
	Write("<form");
	Write(" ");
	Write("role=\"form\"");
	Write(" ");
	Write("action=\"/sheepshead.cgi\"");
	Write(" ");
	Write("method=\"get\"");
	Write(" ");
	Write("style=\"float: left;\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"action\" value=\"report-ytd\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"date\" value=\"");
	Write(Html::EscapeHtml(model.GetPreviousYear()));
	Write("\">");
	Write(" ");
	Write("<button type=\"submit\" class=\"btn\">Previous Year</button>");
	Write(" ");
	Write("</form>");
	Write(" ");
	Write("<form");
	Write(" ");
	Write("role=\"form\"");
	Write(" ");
	Write("action=\"/sheepshead.cgi\"");
	Write(" ");
	Write("method=\"get\"");
	Write(" ");
	Write("style=\"float: right;\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"action\" value=\"report-ytd\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"date\" value=\"");
	Write(Html::EscapeHtml(model.GetNextYear()));
	Write("\">");
	Write(" ");
	Write("<button type=\"submit\" class=\"btn\">Next Year</button>");
	Write(" ");
	Write("</form>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write(" ");
}

void YearNavigationView::SetModel(const YearModel& value)
{
	model = value;
}

