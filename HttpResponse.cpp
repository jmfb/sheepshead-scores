#include "HttpResponse.h"

HttpResponse::HttpResponse(const std::string& contentType, const std::string& content)
	: contentType(contentType), content(content)
{
}

void HttpResponse::SetContentType(const std::string& value)
{
	contentType = value;
}

void HttpResponse::SetContent(const std::string& value)
{
	content = value;
}

const std::string& HttpResponse::GetContentType() const
{
	return contentType;
}

const std::string& HttpResponse::GetContent() const
{
	return content;
}

std::ostream& operator<<(std::ostream& out, const HttpResponse& response)
{
	return out << "Content-type: " << response.GetContentType() << std::endl << std::endl << response.GetContent();
}

