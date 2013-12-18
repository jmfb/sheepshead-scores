#include "UploadScoresView.h"
#include "HtmlUtility.h"
#include "JsonUtility.h"
#include "HeaderView.h"

void UploadScoresView::RenderBody_UploadScores()
{
}

void UploadScoresView::RenderBody_Layout()
{
	Write("<div class=\"well\">");
	Write(" ");
	Write("<h2>Upload Scores</h2>");
	Write(" ");
	Write("<p>Choose a .csv file containing game data to upload.</p>");
	Write(" ");
	Write("<form");
	Write(" ");
	Write("class=\"form-horizontal\"");
	Write(" ");
	Write("role=\"form\"");
	Write(" ");
	Write("action=\"/sheepshead.cgi?action=upload-scores\"");
	Write(" ");
	Write("method=\"post\"");
	Write(" ");
	Write("enctype=\"multipart/form-data\">");
	Write(" ");
	Write("<div class=\"form-group\">");
	Write(" ");
	Write("<div class=\"col-sm-12\">");
	Write(" ");
	Write("<input type=\"file\" name=\"uploadFile\">");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("<div class=\"form-group\">");
	Write(" ");
	Write("<div class=\"col-sm-12\">");
	Write(" ");
	Write("<button type=\"submit\" class=\"btn btn-default btn-primary\">Submit</button>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("</form>");
	Write(" ");
	Write("</div>");
	Write(" ");
	Write(" ");
}

void UploadScoresView::RenderSection_Layout_Header()
{
	Write(" ");
	Write(Partial<HeaderView>(ViewType::UploadScores));
	Write(" ");
	Write(" ");
}

void UploadScoresView::RenderSection_Layout_Title()
{
	Write("Upload Scores");
	Write(" ");
}

