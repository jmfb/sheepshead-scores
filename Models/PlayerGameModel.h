#pragma once
#include <string>

class PlayerGameModel
{
public:
	PlayerGameModel();
	PlayerGameModel(const std::string& date, int score);
	PlayerGameModel(const PlayerGameModel& rhs) = default;
	~PlayerGameModel() = default;
	
	PlayerGameModel& operator=(const PlayerGameModel& rhs) = default;
	
	const std::string& GetDate() const;
	int GetScore() const;

private:
	std::string date;
	int score;
};

