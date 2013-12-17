#include "ReportsView.h"
#include "HtmlUtility.h"
#include "HeaderView.h"

void ReportsView::RenderBody_Reports()
{
}

void ReportsView::RenderBody_Layout()
{
	for (auto report : model.GetReports()) {
	Write(" ");
	Write(model.GetNavigationHtml());
	Write(" ");
	Write("<div class=\"well\" style=\"clear: both;\">");
	Write(" ");
	Write("<h1 style=\"float: left;\">");
	Write(Html::EscapeHtml(report.GetTitle()));
	Write("</h1>");
	Write(" ");
	if (report.CanDelete()) {
	Write(" ");
	Write("<form");
	Write(" ");
	Write("role=\"form\"");
	Write(" ");
	Write("action=\"/sheepshead.cgi\"");
	Write(" ");
	Write("method=\"post\"");
	Write(" ");
	Write("style=\"float: right; position: relative; top: 20px;\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"action\" value=\"delete-game\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"gameId\" value=\"");
	Write(Html::EscapeHtml(report.GetGameId()));
	Write("\">");
	Write(" ");
	Write("<button type=\"submit\" class=\"btn\">Delete</button>");
	Write(" ");
	Write("</form>");
	Write(" ");
	}
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
	Write(Partial<HeaderView>(model.GetViewType()));
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

