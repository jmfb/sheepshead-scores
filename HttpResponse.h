#pragma once
#include <string>
#include <iostream>

class HttpResponse
{
public:
	HttpResponse();
	HttpResponse(const std::string& contentType, const std::string& content, int statusCode = 0);
	HttpResponse(const HttpResponse& rhs) = default;
	~HttpResponse() = default;
	
	HttpResponse& operator=(const HttpResponse& rhs) = default;
	
	void SetContentType(const std::string& value);
	void SetContent(const std::string& value);
	void SetStatusCode(int value);
	
	const std::string& GetContentType() const;
	const std::string& GetContent() const;
	int GetStatusCode() const;
	
private:
	std::string contentType;
	std::string content;
	int statusCode;
};

std::ostream& operator<<(std::ostream& out, const HttpResponse& response);

