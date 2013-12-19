#pragma once
#include "LayoutView.h"
#include "PlayerGamesModel.h"

class PlayerGamesView : public LayoutView
{
public:
	PlayerGamesView() = default;
	PlayerGamesView(const PlayerGamesView& rhs) = delete;
	~PlayerGamesView() = default;

	PlayerGamesView& operator=(const PlayerGamesView& rhs) = delete;

	virtual void RenderBody_PlayerGames();
	virtual void RenderBody_Layout();
	virtual void RenderSection_Layout_Header();
	virtual void RenderSection_Layout_Scripts();
	virtual void RenderSection_Layout_Title();

	void SetModel(const PlayerGamesModel& value);

private:
	PlayerGamesModel model;
};
