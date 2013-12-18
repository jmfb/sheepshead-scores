#include "PlayerGameModel.h"

PlayerGameModel::PlayerGameModel()
	: score(0)
{
}

PlayerGameModel::PlayerGameModel(const std::string& date, int score)
	: date(date), score(score)
{
}

const std::string& PlayerGameModel::GetDate() const
{
	return date;
}

int PlayerGameModel::GetScore() const
{
	return score;
}

