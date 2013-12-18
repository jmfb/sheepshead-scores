#include "MonthNavigationView.h"
#include "HtmlUtility.h"
#include "JsonUtility.h"

void MonthNavigationView::RenderBody_MonthNavigation()
{
}

void MonthNavigationView::RenderBody()
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
	Write("<input type=\"hidden\" name=\"action\" value=\"report-mtd\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"date\" value=\"");
	Write(Html::EscapeHtml(model.GetPreviousMonth()));
	Write("\">");
	Write(" ");
	Write("<button type=\"submit\" class=\"btn\">Previous Month</button>");
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
	Write("<input type=\"hidden\" name=\"action\" value=\"report-mtd\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"date\" value=\"");
	Write(Html::EscapeHtml(model.GetNextMonth()));
	Write("\">");
	Write(" ");
	Write("<button type=\"submit\" class=\"btn\">Next Month</button>");
	Write(" ");
	Write("</form>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write(" ");
}

void MonthNavigationView::SetModel(const MonthModel& value)
{
	model = value;
}

