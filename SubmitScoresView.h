#pragma once
#include "LayoutView.h"

class SubmitScoresView : public LayoutView
{
public:
	SubmitScoresView() = default;
	SubmitScoresView(const SubmitScoresView& rhs) = delete;
	~SubmitScoresView() = default;

	SubmitScoresView& operator=(const SubmitScoresView& rhs) = delete;

	virtual void RenderBody_SubmitScores();
	virtual void RenderBody_Layout();
	virtual void RenderSection_Layout_Body();
	virtual void RenderSection_Layout_Title();

};
