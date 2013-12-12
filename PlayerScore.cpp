#include "PlayerScore.h"

PlayerScore::PlayerScore()
	: score(0)
{
}

PlayerScore::PlayerScore(const std::string& name, int score)
	: name(name), score(score)
{
}

void PlayerScore::SetName(const std::string& value)
{
	name = value;
}

void PlayerScore::SetScore(int value)
{
	score = value;
}

const std::string& PlayerScore::GetName() const
{
	return name;
}

int PlayerScore::GetScore() const
{
	return score;
}

PlayerScore PlayerScore::Load(pqxx::result::tuple& result, int nameIndex, int scoreIndex)
{
	return { result[nameIndex].as<std::string>(), result[scoreIndex].as<int>() };
}

PlayerScore PlayerScore::Load(const FormData& formData, int number)
{
	auto player = "player" + std::to_string(number);
	return { formData(player + "Name"), std::stoi(formData(player + "Score")) };
}

std::vector<PlayerScore> PlayerScore::LoadAll(pqxx::result& results, int nameIndex, int scoreIndex)
{
	std::vector<PlayerScore> playerScores;
	for (auto result : results)
		playerScores.push_back(Load(result, nameIndex, scoreIndex));
	return playerScores;
}

std::vector<PlayerScore> PlayerScore::LoadAll(const FormData& formData)
{
	std::vector<PlayerScore> playerScores;
	for (auto number = 1; number <= 6; ++number)
	{
		auto playerScore = Load(formData, number);
		if (!playerScore.GetName().empty())
			playerScores.push_back(playerScore);
	}
	return playerScores;
}

