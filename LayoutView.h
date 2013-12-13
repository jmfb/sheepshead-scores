#pragma once
#include "BaseView.h"

class LayoutView : public BaseView
{
public:
	LayoutView() = default;
	LayoutView(const LayoutView& rhs) = delete;
	~LayoutView() = default;

	LayoutView& operator=(const LayoutView& rhs) = delete;

	virtual void RenderBody_Layout();
	virtual void RenderBody();

};
