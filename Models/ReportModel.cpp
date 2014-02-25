#include "ReportModel.h"

ReportModel::ReportModel()
	: canDelete(false), gameId(0)
{
}

void ReportModel::SetTitle(const std::string& value)
{
	title = value;
}

void ReportModel::AddPlayerScore(const PlayerScoreModel& value)
{
	playerScores.push_back(value);
}

void ReportModel::SetGameId(int value)
{
	canDelete = true;
	gameId = value;
}

const std::string& ReportModel::GetTitle() const
{
	return title;
}

const std::vector<PlayerScoreModel>& ReportModel::GetPlayerScores() const
{
	return playerScores;
}

int ReportModel::GetPointSpread() const
{
	auto pointSpread = 0;
	for (auto playerScore : playerScores)
		if (playerScore.GetScore() > 0)
			pointSpread += playerScore.GetScore();
	return pointSpread;
}

bool ReportModel::CanDelete() const
{
	return canDelete;
}

int ReportModel::GetGameId() const
{
	return gameId;
}

std::string ReportModel::ToJson() const
{
	return Json::Jsonify(
		"gameId", gameId,
		"title", title,
		"playerScores", playerScores,
		"pointSpread", GetPointSpread());
}

