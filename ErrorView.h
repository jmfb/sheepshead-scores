#pragma once
#include "LayoutView.h"
#include "ErrorLinesModel.h"

class ErrorView : public LayoutView
{
public:
	ErrorView() = default;
	ErrorView(const ErrorView& rhs) = delete;
	~ErrorView() = default;

	ErrorView& operator=(const ErrorView& rhs) = delete;

	virtual void RenderBody_Error();
	virtual void RenderBody_Layout();
	virtual void RenderSection_Layout_Body();
	virtual void RenderSection_Layout_Title();

	void SetModel(const ErrorLinesModel& value);

private:
	ErrorLinesModel model;
};
