#include "PlayerGamesModel.h"
#include <sstream>

PlayerGamesModel::PlayerGamesModel()
	: year(0)
{
}

void PlayerGamesModel::SetPlayer(const std::string& value)
{
	player = value;
}

void PlayerGamesModel::SetDate(const std::string& value)
{
	std::istringstream in(value);
	in >> year;
	if (year < 1900)
		year = 1900;
	if (year > 3000)
		year = 3000;
	
	std::ostringstream out;
	out << year << "-1-1";
	beginningOfYear = out.str();
	out.str("");
	
	out << (year - 1) << "-1-1";
	previousYear = out.str();
	out.str("");
	
	out << (year + 1) << "-1-1";
	nextYear = out.str();
}

void PlayerGamesModel::AddGame(const PlayerGameModel& value)
{
	games.push_back(value);
}

const std::string& PlayerGamesModel::GetPlayer() const
{
	return player;
}

int PlayerGamesModel::GetYear() const
{
	return year;
}

const std::string& PlayerGamesModel::GetBeginningOfYear() const
{
	return beginningOfYear;
}

const std::string& PlayerGamesModel::GetPreviousYear() const
{
	return previousYear;
}

const std::string& PlayerGamesModel::GetNextYear() const
{
	return nextYear;
}

const std::vector<PlayerGameModel>& PlayerGamesModel::GetGames() const
{
	return games;
}

int PlayerGamesModel::GetScoreTotal() const
{
	int scoreTotal = 0;
	for (auto game : games)
		scoreTotal += game.GetScore();
	return scoreTotal;
}

GraphModel PlayerGamesModel::GetGraph() const
{
	GraphModel model;
	GraphDataModel currentData;
	currentData.SetColor(220, 220, 220);
	GraphDataModel totalData;
	totalData.SetColor(151, 187, 205);
	auto totalScore = 0;
	for (auto iter = games.rbegin(); iter != games.rend(); ++iter)
	{
		auto game = *iter;
		model.AddLabel("");
		auto score = game.GetScore();
		currentData.AddData(score);
		totalScore += score;
		totalData.AddData(totalScore);
	}
	model.AddData(currentData);
	model.AddData(totalData);
	return model;
}

GraphOptionsModel PlayerGamesModel::GetGraphOptions() const
{
	auto minValue = 0;
	auto maxValue = 0;
	auto totalScore = 0;
	for (auto iter = games.rbegin(); iter != games.rend(); ++iter)
	{
		auto game = *iter;
		auto score = game.GetScore();
		totalScore += score;
		if (score < minValue)
			minValue = score;
		if (totalScore < minValue)
			minValue = totalScore;
		if (score > maxValue)
			maxValue = score;
		if (totalScore > maxValue)
			maxValue = totalScore;
	}
	GraphOptionsModel model;
	model.SetMinValue(minValue);
	model.SetMaxValue(maxValue);
	return model;	
}

