#include "GraphModel.h"

void GraphModel::AddLabel(const std::string& value)
{
	labels.push_back(value);
}

void GraphModel::AddData(const GraphDataModel& value)
{
	datasets.push_back(value);
}

std::string GraphModel::ToObject() const
{
	return Json::JsonifyObject(
		"labels", labels,
		"datasets", datasets);
}

