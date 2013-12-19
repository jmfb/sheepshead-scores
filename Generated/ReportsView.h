#pragma once
#include "LayoutView.h"
#include "ReportsModel.h"

class ReportsView : public LayoutView
{
public:
	ReportsView() = default;
	ReportsView(const ReportsView& rhs) = delete;
	~ReportsView() = default;

	ReportsView& operator=(const ReportsView& rhs) = delete;

	virtual void RenderBody_Reports();
	virtual void RenderBody_Layout();
	virtual void RenderSection_Layout_Header();
	virtual void RenderSection_Layout_Scripts();
	virtual void RenderSection_Layout_Title();

	void SetModel(const ReportsModel& value);

private:
	ReportsModel model;
};
