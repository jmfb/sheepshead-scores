#pragma once
#include <string>
#include "json/value.h"

class JsonPostData
{
public:
	JsonPostData();
	JsonPostData(const JsonPostData& rhs) = default;
	~JsonPostData() = default;
	
	JsonPostData& operator=(const JsonPostData& rhs) = default;
	
	const Json::Value& GetJson() const;
	
private:
	Json::Value json;
};

