#pragma once
#include "JsonUtility.h"
#include <string>
#include <vector>

class NameLookupModel : public Json::IWriter
{
public:
	NameLookupModel() = default;
	NameLookupModel(const NameLookupModel& rhs) = default;
	~NameLookupModel() = default;
	
	NameLookupModel& operator=(const NameLookupModel& rhs) = default;
	
	void AddName(const std::string& value);

	std::string ToJson() const;

private:
	std::vector<std::string> names;
};

