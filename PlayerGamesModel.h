#pragma once
#include "PlayerGameModel.h"
#include <string>
#include <vector>

class PlayerGamesModel
{
public:
	PlayerGamesModel();
	PlayerGamesModel(const PlayerGamesModel& rhs) = default;
	~PlayerGamesModel() = default;
	
	PlayerGamesModel& operator=(const PlayerGamesModel& rhs) = default;
	
	void SetPlayer(const std::string& value);
	void SetDate(const std::string& value);
	void AddGame(const PlayerGameModel& value);
	
	const std::string& GetPlayer() const;
	int GetYear() const;
	const std::string& GetBeginningOfYear() const;
	const std::string& GetPreviousYear() const;
	const std::string& GetNextYear() const;
	const std::vector<PlayerGameModel>& GetGames() const;
	int GetScoreTotal() const;
	
private:
	std::string player;
	int year;
	std::string beginningOfYear;
	std::string previousYear;
	std::string nextYear;
	std::vector<PlayerGameModel> games;
};

