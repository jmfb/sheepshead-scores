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
	virtual void RenderSection_Layout_Title();
	virtual void RenderSection_Layout_Scripts();
	virtual void RenderBody();

};
