#pragma once
#include "BaseView.h"
#include "YearModel.h"

class YearNavigationView : public BaseView
{
public:
	YearNavigationView() = default;
	YearNavigationView(const YearNavigationView& rhs) = delete;
	~YearNavigationView() = default;

	YearNavigationView& operator=(const YearNavigationView& rhs) = delete;

	virtual void RenderBody_YearNavigation();
	virtual void RenderBody();

	void SetModel(const YearModel& value);

private:
	YearModel model;
};
