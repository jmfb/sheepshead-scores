#pragma once
#include "NameLookupModel.h"
#include "ReportModel.h"
#include "ReportsModel.h"
#include "PlayerScoreModel.h"
#include "PlayerGameModel.h"
#include "HandModel.h"
#include "GameForPlayersModel.h"
#include <string>
#include <vector>

class DataBridge
{
public:
	NameLookupModel LookupNames(const std::string& query);
	ReportModel ReportHands(
		const std::string& date,
		const std::vector<std::string>& playerNames,
		const std::vector<HandModel>& hands);
	ReportModel ReportScores(const std::string& date, const std::vector<PlayerScoreModel>& playerScores);
	ReportModel ReportScoresSince(const std::string& since, const std::string& until, const std::string& title);
	std::vector<PlayerGameModel> ReportPlayerGames(
		const std::string& player,
		const std::string& since,
		const std::string& until);
	ReportsModel FindGames(int skip, int take);
	void DeleteGame(int gameId);
	std::vector<GameForPlayersModel> GetGamesByDateForPlayers(
		const std::vector<std::string>& playerNames,
		const std::string& since,
		const std::string& until);
	std::vector<PlayerScoreModel> GetScoresByDate(
		const std::string& since,
		const std::string& until);
};

