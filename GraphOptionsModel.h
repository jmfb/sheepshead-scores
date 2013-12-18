#pragma once
#include "JsonUtility.h"

class GraphOptionsModel : public Json::IWriter
{
public:
	GraphOptionsModel();
	GraphOptionsModel(const GraphOptionsModel& rhs) = default;
	~GraphOptionsModel() = default;
	
	GraphOptionsModel& operator=(const GraphOptionsModel& rhs) = default;

	void SetMinValue(int value);
	void SetMaxValue(int value);
	
	std::string ToObject() const;
	
private:
	int minValue;
	int maxValue;
};

