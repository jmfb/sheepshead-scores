#include "PlayerGamesView.h"
#include "HtmlUtility.h"
#include "HeaderView.h"

void PlayerGamesView::RenderBody_PlayerGames()
{
}

void PlayerGamesView::RenderBody_Layout()
{
	Write("<div ng-controller=\"PlayerGamesCtrl\" ng-cloak>");
	Write(" ");
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
	Write("<input type=\"hidden\" name=\"action\" value=\"report-player\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"player\" value=\"{{player}}\">");
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
	Write("<input type=\"hidden\" name=\"action\" value=\"report-player\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"player\" value=\"{{player}}\">");
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
	Write("<div class=\"well\">");
	Write(" ");
	Write("<h2>Player Report -&nbsp;");
	Write(Html::EscapeHtml(model.GetYear()));
	Write("</h2>");
	Write(" ");
	Write("<form class=\"form-horizontal\" role=\"form\" action=\"/sheepshead.cgi\" method=\"get\">");
	Write(" ");
	Write("<div class=\"form-group\">");
	Write(" ");
	Write("<div class=\"col-sm-3\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"action\" value=\"report-player\">");
	Write(" ");
	Write("<input");
	Write(" ");
	Write("class=\"form-control\"");
	Write(" ");
	Write("type=\"text\"");
	Write(" ");
	Write("name=\"player\"");
	Write(" ");
	Write("ng-model=\"player\"");
	Write(" ");
	Write("placeholder=\"Name\"");
	Write(" ");
	Write("value=\"");
	Write(Html::EscapeHtml(model.GetPlayer()));
	Write("\">");
	Write(" ");
	Write("<input type=\"hidden\" name=\"date\" value=\"");
	Write(Html::EscapeHtml(model.GetBeginningOfYear()));
	Write("\">");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("<div class=\"col-sm-3\">");
	Write(" ");
	Write("<button type=\"submit\" class=\"btn btn-primary btn-default\">Submit</button>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("</form>");
	Write(" ");
	Write("<table class=\"table table-striped\">");
	Write(" ");
	Write("<thead>");
	Write(" ");
	Write("<tr>");
	Write(" ");
	Write("<th>Date</th>");
	Write(" ");
	Write("<th>Score</th>");
	Write(" ");
	Write("</tr>");
	Write(" ");
	Write("</thead>");
	Write(" ");
	Write("<tbody>");
	Write(" ");
	for (auto game : model.GetGames()) {
	Write(" ");
	Write("<tr>");
	Write(" ");
	Write("<td>");
	Write(Html::EscapeHtml(game.GetDate()));
	Write("</td>");
	Write(" ");
	Write("<td>");
	Write(Html::EscapeHtml(game.GetScore()));
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
	Write("<td>Total</td>");
	Write(" ");
	Write("<td>");
	Write(Html::EscapeHtml(model.GetScoreTotal()));
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
	Write("</div>");
	Write(" ");
	Write(" ");
}

void PlayerGamesView::RenderSection_Layout_Header()
{
	Write(" ");
	Write(Partial<HeaderView>(ViewType::ReportPlayer));
	Write(" ");
	Write(" ");
}

void PlayerGamesView::RenderSection_Layout_Scripts()
{
	Write(" ");
	Write("<script>");
	Write(" ");
	Write("window.initialData = \"");
	Write(Html::EscapeHtml(model.GetPlayer()));
	Write("\";");
	Write(" ");
	Write("</script>");
	Write(" ");
	Write("<script src=\"PlayerGamesCtrl.js\"></script>");
	Write(" ");
	Write(" ");
}

void PlayerGamesView::RenderSection_Layout_Title()
{
	Write("Player Scores");
	Write(" ");
}

void PlayerGamesView::SetModel(const PlayerGamesModel& value)
{
	model = value;
}

