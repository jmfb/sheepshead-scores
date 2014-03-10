#include "GameForPlayersModel.h"

GameForPlayersModel::GameForPlayersModel()
	: gameId(0)
{
}

void GameForPlayersModel::SetGameId(int value)
{
	gameId = value;
}

void GameForPlayersModel::SetPlayedWhen(const std::string& value)
{
	playedWhen = value;
}

void GameForPlayersModel::AddPlayerScore(const PlayerScoreModel& value)
{
	playerScores.push_back(value);
}

int GameForPlayersModel::GetGameId() const
{
	return gameId;
}

std::string GameForPlayersModel::ToJson() const
{
	return Json::Jsonify(
		"gameId", gameId,
		"playedWhen", playedWhen,
		"playerScores", playerScores);
}
