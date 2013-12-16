#include "SubmitScoresView.h"
#include "HtmlUtility.h"

void SubmitScoresView::RenderBody_SubmitScores()
{
}

void SubmitScoresView::RenderBody_Layout()
{
	Write("<div class=\"well\" ng-controller=\"SheepsheadScoreCtrl\" ng-cloak>");
	Write(" ");
	Write("<h2>Sheepshead Scores</h2>");
	Write(" ");
	Write("<form class=\"form-horizontal\" role=\"form\" action=\"/sheepshead.cgi\" method=\"post\">");
	Write(" ");
	Write("<div");
	Write(" ");
	Write("class=\"form-group\"");
	Write(" ");
	Write("on-repeat-done=\"autocomplete\"");
	Write(" ");
	Write("ng-repeat=\"playerScore in playerScores\">");
	Write(" ");
	Write("<div class=\"col-sm-3\">");
	Write(" ");
	Write("<input");
	Write(" ");
	Write("type=\"text\"");
	Write(" ");
	Write("class=\"form-control name-lookup\"");
	Write(" ");
	Write("name=\"{{playerScore.nameId}}\"");
	Write(" ");
	Write("placeholder=\"Name\"");
	Write(" ");
	Write("ng-model=\"playerScore.name\"");
	Write(" ");
	Write("autocomplete=\"off\">");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("<div class=\"col-sm-2\">");
	Write(" ");
	Write("<input");
	Write(" ");
	Write("type=\"number\"");
	Write(" ");
	Write("class=\"form-control\"");
	Write(" ");
	Write("name=\"{{playerScore.scoreId}}\"");
	Write(" ");
	Write("placeholder=\"Score\"");
	Write(" ");
	Write("ng-model=\"playerScore.score\">");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("<div class=\"form-group\">");
	Write(" ");
	Write("<div class=\"col-sm-5\">");
	Write(" ");
	Write("<p");
	Write(" ");
	Write("class=\"form-control-static\"");
	Write(" ");
	Write("style=\"float: right;\">");
	Write(" ");
	Write("P.S. {{getPositivePointSpread()}}");
	Write(" ");
	Write("</p>");
	Write(" ");
	Write("<button");
	Write(" ");
	Write("type=\"submit\"");
	Write(" ");
	Write("class=\"btn btn-default btn-primary\"");
	Write(" ");
	Write("ng-disabled=\"!isValid()\">");
	Write(" ");
	Write("Submit");
	Write(" ");
	Write("</button>");
	Write(" ");
	Write("<button");
	Write(" ");
	Write("type=\"button\"");
	Write(" ");
	Write("class=\"btn btn-link\"");
	Write(" ");
	Write("ng-click=\"addPlayer()\">");
	Write(" ");
	Write("+ Add a Player");
	Write(" ");
	Write("</button>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("<input type=\"hidden\" name=\"playerCount\" value=\"{{playerCount}}\">");
	Write(" ");
	Write("</form>");
	Write(" ");
	Write("<div");
	Write(" ");
	Write("ng-show=\"getCheckSum()\"");
	Write(" ");
	Write("class=\"alert alert-danger\">");
	Write(" ");
	Write("Checksum is {{getCheckSum()}} instead of 0.");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write(" ");
}

void SubmitScoresView::RenderSection_Layout_Header()
{
	Write(" ");
	Write("<li class=\"active\"><a href=\"#\">Home</a></li>");
	Write(" ");
	Write("<li><a href=\"/sheepshead.cgi?action=report-mtd\">MTD Scores</a></li>");
	Write(" ");
	Write("<li><a href=\"/sheepshead.cgi?action=report-ytd\">YTD Scores</a></li>");
	Write(" ");
	Write("<li><a href=\"/sheepshead.cgi?action=report-history\">History</a></li>");
	Write(" ");
	Write(" ");
}

void SubmitScoresView::RenderSection_Layout_Scripts()
{
	Write(" ");
	Write("<script src=\"SheepsheadScoreCtrl.js\"></script>");
	Write(" ");
	Write(" ");
}

void SubmitScoresView::RenderSection_Layout_Title()
{
	Write("Sheepshead Scores");
	Write(" ");
}

