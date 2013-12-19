#pragma once
#include "LayoutView.h"

class UploadScoresView : public LayoutView
{
public:
	UploadScoresView() = default;
	UploadScoresView(const UploadScoresView& rhs) = delete;
	~UploadScoresView() = default;

	UploadScoresView& operator=(const UploadScoresView& rhs) = delete;

	virtual void RenderBody_UploadScores();
	virtual void RenderBody_Layout();
	virtual void RenderSection_Layout_Header();
	virtual void RenderSection_Layout_Title();

};
