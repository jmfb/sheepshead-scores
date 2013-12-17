#pragma once
#include "BaseView.h"
#include "MonthModel.h"

class MonthNavigationView : public BaseView
{
public:
	MonthNavigationView() = default;
	MonthNavigationView(const MonthNavigationView& rhs) = delete;
	~MonthNavigationView() = default;

	MonthNavigationView& operator=(const MonthNavigationView& rhs) = delete;

	virtual void RenderBody_MonthNavigation();
	virtual void RenderBody();

	void SetModel(const MonthModel& value);

private:
	MonthModel model;
};
