#pragma once
#include "BaseView.h"
#include "ViewType.h"

class HeaderView : public BaseView
{
public:
	HeaderView() = default;
	HeaderView(const HeaderView& rhs) = delete;
	~HeaderView() = default;

	HeaderView& operator=(const HeaderView& rhs) = delete;

	virtual void RenderBody_Header();
	virtual void RenderBody();

	void SetModel(const ViewType& value);

private:
	ViewType model;
};
