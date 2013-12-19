#pragma once
#include "JsonUtility.h"
#include <vector>

class GraphDataModel : public Json::IWriter
{
public:
	GraphDataModel();
	GraphDataModel(const GraphDataModel& rhs) = default;
	~GraphDataModel() = default;
	
	GraphDataModel& operator=(const GraphDataModel& rhs) = default;
	
	void SetColor(int red, int green, int blue);
	void AddData(int value);
	
	std::string ToObject() const;
	
private:
	int red;
	int green;
	int blue;
	std::vector<int> data;
};

