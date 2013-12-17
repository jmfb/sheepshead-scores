#pragma once
#include "NameLookupModel.h"
#include "ReportModel.h"
#include "ReportsModel.h"
#include "PlayerScoreModel.h"
#include <string>
#include <vector>

class DataBridge
{
public:
	NameLookupModel LookupNames(const std::string& query);
	ReportModel ReportScores(const std::string& date, const std::vector<PlayerScoreModel>& playerScores);
	ReportModel ReportScoresSince(const std::string& since, const std::string& until, const std::string& title);
	ReportsModel FindGames(int skip, int take);
	void DeleteGame(int gameId);
};

