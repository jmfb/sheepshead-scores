#pragma once
#include "HttpRequest.h"
#include "HttpResponse.h"
#include <string>

class BaseController
{
public:
	BaseController() = default;
	BaseController(const BaseController& rhs) = delete;
	~BaseController() = default;
	
	BaseController& operator=(const BaseController& rhs) = delete;
	
	virtual HttpResponse Execute() = 0;
	
protected:
	HttpResponse Error(const std::string& error, int statusCode);

	HttpRequest request;
};

