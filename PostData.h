#pragma once
#include "FormData.h"

class PostData : public FormData
{
public:
	PostData();
	PostData(const PostData& rhs) = default;
	~PostData() = default;
	
	PostData& operator=(const PostData& rhs) = default;
};

