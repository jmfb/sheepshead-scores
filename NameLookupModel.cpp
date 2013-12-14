#include "NameLookupModel.h"

void NameLookupModel::AddName(const std::string& value)
{
	names.push_back(value);
}

std::string NameLookupModel::ToJson() const
{
	return Json::Jsonify("names", names);
}

