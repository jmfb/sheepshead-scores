#include "GraphOptionsModel.h"

GraphOptionsModel::GraphOptionsModel()
	: minValue(0), maxValue(0)
{
}

void GraphOptionsModel::SetMinValue(int value)
{
	minValue = value;
}

void GraphOptionsModel::SetMaxValue(int value)
{
	maxValue = value;
}

std::string GraphOptionsModel::ToObject() const
{
	const auto steps = 20;
	auto range = maxValue - minValue;
	auto increment = range / steps;
	return Json::JsonifyObject(
		"scaleOverride", true,
		"scaleSteps", steps,
		"scaleStepWidth", increment,
		"scaleStartValue", minValue);
}

