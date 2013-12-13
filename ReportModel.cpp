#include "ReportModel.h"

void ReportModel::SetTitle(const std::string& value)
{
	title = value;
}

void ReportModel::AddPlayerScore(const PlayerScoreModel& value)
{
	playerScores.push_back(value);
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

