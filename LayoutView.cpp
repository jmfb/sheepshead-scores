#include "LayoutView.h"
#include "HtmlUtility.h"

void LayoutView::RenderBody_Layout()
{
}

void LayoutView::RenderSection_Layout_Title()
{
}

void LayoutView::RenderBody()
{
	Write("<!DOCTYPE html>");
	Write(" ");
	Write("<html lang=\"en\" ng-app=\"sheepsheadApp\">");
	Write(" ");
	Write("<head>");
	Write(" ");
	Write("<meta charset=\"utf-8\">");
	Write(" ");
	Write("<title>");
	RenderSection_Layout_Title();
	Write("</title>");
	Write(" ");
	Write("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
	Write(" ");
	Write("<meta name=\"author\" content=\"Jacob Buysse\">");
	Write(" ");
	Write("<meta name=\"description\" content=\"Sheepshead Scores\">");
	Write(" ");
	Write("<link href=\"//netdna.bootstrapcdn.com/bootstrap/3.0.3/css/bootstrap.min.css\" rel=\"stylesheet\">");
	Write(" ");
	Write("<link href=\"//netdna.bootstrapcdn.com/font-awesome/4.0.1/css/font-awesome.min.css\" rel=\"stylesheet\">");
	Write(" ");
	Write("<link href=\"//code.jquery.com/ui/1.10.3/themes/smoothness/jquery-ui.css\" rel=\"stylesheet\">");
	Write(" ");
	Write("<link href=\"styles.css\" rel=\"stylesheet\">");
	Write(" ");
	Write("<script src=\"//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js\"></script>");
	Write(" ");
	Write("<script src=\"//ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/jquery-ui.min.js\"></script>");
	Write(" ");
	Write("<script src=\"//netdna.bootstrapcdn.com/bootstrap/3.0.3/js/bootstrap.min.js\"></script>");
	Write(" ");
	Write("<script src=\"//ajax.googleapis.com/ajax/libs/angularjs/1.2.4/angular.min.js\"></script>");
	Write(" ");
	Write("<script src=\"controllers.js\"></script>");
	Write(" ");
	Write("</head>");
	Write(" ");
	Write("<body ng-controller=\"SheepsheadScoreCtrl\">");
	Write(" ");
	Write("<div class=\"container\">");
	Write(" ");
	RenderBody_Layout();
	Write(" ");
	Write("</div>");
	Write(" ");
	Write("<script src=\"initialize.js\"></script>");
	Write(" ");
	Write("</body>");
	Write(" ");
	Write("</html>");
	Write(" ");
	Write(" ");
}

