#pragma once
#include "GraphDataModel.h"
#include "JsonUtility.h"
#include <string>
#include <vector>

class GraphModel : public Json::IWriter
{
public:
	GraphModel() = default;
	GraphModel(const GraphModel& rhs) = default;
	~GraphModel() = default;
	
	GraphModel& operator=(const GraphModel& rhs) = default;
	
	void AddLabel(const std::string& value);
	void AddData(const GraphDataModel& value);
	
	std::string ToObject() const;

private:
	std::vector<std::string> labels;
	std::vector<GraphDataModel> datasets;
};

