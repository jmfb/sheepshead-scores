#include "GraphDataModel.h"
#include <sstream>

GraphDataModel::GraphDataModel()
	: red(0), green(0), blue(0)
{
}

void GraphDataModel::SetColor(int red, int green, int blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void GraphDataModel::AddData(int value)
{
	data.push_back(value);
}

std::string GraphDataModel::ToObject() const
{
	std::ostringstream halfColor;
	std::ostringstream fullColor;
	halfColor << "rgba(" << red << "," << green << "," << blue << ",0.5)";
	fullColor << "rgba(" << red << "," << green << "," << blue << ",1)";
	return Json::JsonifyObject(
		"fillColor", halfColor.str(),
		"strokeColor", fullColor.str(),
		"pointColor", fullColor.str(),
		"pointStrokeColor", "#fff",
		"data", data);
}

