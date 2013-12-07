#pragma once
#include "FormData.h"

class QueryString : public FormData
{
public:
	QueryString();
	QueryString(const QueryString& rhs) = default;
	~QueryString() = default;
	
	QueryString& operator=(const QueryString& rhs) = default;
};

