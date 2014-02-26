#include "JsonPostData.h"
#include "HttpContext.h"
#include "json/reader.h"

JsonPostData::JsonPostData()
{
	auto postData = HttpContext::ReadPostDataOfType(ContentTypes::Json);
	if (postData.empty())
		return;
	Json::Reader reader;
	reader.parse(postData, json);
}

const Json::Value& JsonPostData::GetJson() const
{
	return json;
}

