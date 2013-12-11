#include "HttpResponse.h"

HttpResponse::HttpResponse()
	: statusCode(0)
{
}

HttpResponse::HttpResponse(const std::string& contentType, const std::string& content, int statusCode)
	: contentType(contentType), content(content), statusCode(statusCode)
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

void HttpResponse::SetStatusCode(int value)
{
	statusCode = value;
}

const std::string& HttpResponse::GetContentType() const
{
	return contentType;
}

const std::string& HttpResponse::GetContent() const
{
	return content;
}

int HttpResponse::GetStatusCode() const
{
	return statusCode;
}

std::ostream& operator<<(std::ostream& out, const HttpResponse& response)
{
	if (response.GetStatusCode() != 0)
		out << "Status: " << response.GetStatusCode() << std::endl;
	return out << "Content-type: " << response.GetContentType() << std::endl
		<< "Content-length: " << response.GetContent().size() << std::endl
		<< std::endl
		<< response.GetContent();
}

