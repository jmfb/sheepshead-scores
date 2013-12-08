#pragma once
#include <string>
#include <iostream>

class HttpResponse
{
public:
	HttpResponse() = default;
	HttpResponse(const std::string& contentType, const std::string& content);
	HttpResponse(const HttpResponse& rhs) = default;
	~HttpResponse() = default;
	
	HttpResponse& operator=(const HttpResponse& rhs) = default;
	
	void SetContentType(const std::string& value);
	void SetContent(const std::string& value);
	
	const std::string& GetContentType() const;
	const std::string& GetContent() const;
	
private:
	std::string contentType;
	std::string content;
};

std::ostream& operator<<(std::ostream& out, const HttpResponse& response);

