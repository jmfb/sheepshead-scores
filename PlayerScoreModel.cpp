#include "PlayerScoreModel.h"

PlayerScoreModel::PlayerScoreModel()
	: score(0)
{
}

PlayerScoreModel::PlayerScoreModel(const std::string& name, int score)
	: name(name), score(score)
{
}

void PlayerScoreModel::SetName(const std::string& value)
{
	name = value;
}

void PlayerScoreModel::SetScore(int value)
{
	score = value;
}

const std::string& PlayerScoreModel::GetName() const
{
	return name;
}

int PlayerScoreModel::GetScore() const
{
	return score;
}

PlayerScoreModel PlayerScoreModel::Load(pqxx::result::tuple& result, int nameIndex, int scoreIndex)
{
	return { result[nameIndex].as<std::string>(), result[scoreIndex].as<int>() };
}

PlayerScoreModel PlayerScoreModel::Load(const FormData& formData, int number)
{
	auto player = "player" + std::to_string(number);
	return { formData(player + "Name"), std::stoi(formData(player + "Score")) };
}

std::vector<PlayerScoreModel> PlayerScoreModel::LoadAll(pqxx::result& results, int nameIndex, int scoreIndex)
{
	std::vector<PlayerScoreModel> playerScores;
	for (auto result : results)
		playerScores.push_back(Load(result, nameIndex, scoreIndex));
	return playerScores;
}

std::vector<PlayerScoreModel> PlayerScoreModel::LoadAll(const FormData& formData)
{
	std::vector<PlayerScoreModel> playerScores;
	for (auto number = 1; number <= 6; ++number)
	{
		auto playerScore = Load(formData, number);
		if (!playerScore.GetName().empty())
			playerScores.push_back(playerScore);
	}
	return playerScores;
}

