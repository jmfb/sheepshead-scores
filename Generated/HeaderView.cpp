#include "HeaderView.h"
#include "HtmlUtility.h"
#include "JsonUtility.h"
#include "HeaderLinks.h"

void HeaderView::RenderBody_Header()
{
}

void HeaderView::RenderBody()
{
	for (auto link : GetHeaderLinks()) {
	Write(" ");
	Write("<li class=\"");
	Write(Html::EscapeHtml(link.GetLinkClass(model)));
	Write("\">");
	Write(" ");
	Write("<a href=\"");
	Write(Html::EscapeHtml(link.GetLinkHref(model)));
	Write("\">");
	Write(" ");
	Write(Html::EscapeHtml(link.GetLinkLabel()));
	Write(" ");
	Write("</a>");
	Write(" ");
	Write("</li>");
	Write(" ");
	}
	Write(" ");
	Write(" ");
}

void HeaderView::SetModel(const ViewType& value)
{
	model = value;
}

