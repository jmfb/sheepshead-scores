#include "ReportsView.h"
#include "HtmlUtility.h"

void ReportsView::RenderBody_Reports()
{
}

void ReportsView::RenderBody_Layout()
{
	for (auto report : model.GetReports()) {
	Write(" ");
	Write("<div class=\"well\">");
	Write(" ");
	Write("<h1>");
	Write(Html::EscapeHtml(report.GetTitle()));
	Write("</h1>");
	Write(" ");
	Write("<table class=\"table table-striped\">");
	Write(" ");
	Write("<thead>");
	Write(" ");
	Write("<tr>");
	Write(" ");
	Write("<th>Player</th>");
	Write(" ");
	Write("<th>Score</th>");
	Write(" ");
	Write("</tr>");
	Write(" ");
	Write("</thead>");
	Write(" ");
	Write("<tbody>");
	Write(" ");
	for (auto playerScore : report.GetPlayerScores()) {
	Write(" ");
	Write("<tr>");
	Write(" ");
	Write("<td>");
	Write(Html::EscapeHtml(playerScore.GetName()));
	Write("</td>");
	Write(" ");
	Write("<td>");
	Write(Html::EscapeHtml(playerScore.GetScore()));
	Write("</td>");
	Write(" ");
	Write("</tr>");
	Write(" ");
	}
	Write(" ");
	Write("</tbody>");
	Write(" ");
	Write("<tfoot>");
	Write(" ");
	Write("<tr class=\"success\">");
	Write(" ");
	Write("<td>P.S.</td>");
	Write(" ");
	Write("<td>");
	Write(Html::EscapeHtml(report.GetPointSpread()));
	Write("</td>");
	Write(" ");
	Write("</tr>");
	Write(" ");
	Write("</tfoot>");
	Write(" ");
	Write("</table>");
	Write(" ");
	Write("</div>");
	Write(" ");
	}
	Write(" ");
	Write(" ");
}

void ReportsView::RenderSection_Layout_Header()
{
	Write(" ");
	Write("<li><a href=\"/sheepshead.cgi\">Home</a></li>");
	Write(" ");
	for (auto reportLink : model.GetReportLinks()) {
	Write(" ");
	Write("<li class=\"");
	Write(Html::EscapeHtml(reportLink.GetLinkClass()));
	Write("\">");
	Write(" ");
	Write("<a href=\"");
	Write(Html::EscapeHtml(reportLink.GetLinkHref()));
	Write("\">");
	Write(" ");
	Write(Html::EscapeHtml(reportLink.GetLinkLabel()));
	Write(" ");
	Write("</a>");
	Write(" ");
	Write("</li>");
	Write(" ");
	}
	Write(" ");
	Write(" ");
}

void ReportsView::RenderSection_Layout_Title()
{
	Write("Sheepshead Scores");
	Write(" ");
}

void ReportsView::SetModel(const ReportsModel& value)
{
	model = value;
}

