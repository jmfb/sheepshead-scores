#pragma once
#include <string>
#include "PlayerScoreModel.h"
#include "JsonUtility.h"

class GameForPlayersModel : public Json::IWriter
{
public:
	GameForPlayersModel();
	GameForPlayersModel(const GameForPlayersModel& rhs) = default;
	~GameForPlayersModel() = default;

	GameForPlayersModel& operator=(const GameForPlayersModel& rhs) = default;

	void SetGameId(int value);
	void SetPlayedWhen(const std::string& value);
	void AddPlayerScore(const PlayerScoreModel& value);

	int GetGameId() const;

	std::string ToJson() const;

private:
	int gameId;
	std::string playedWhen;
	std::vector<PlayerScoreModel> playerScores;
};