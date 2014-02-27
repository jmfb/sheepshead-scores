#include "HandsModel.h"
#include "StringUtility.h"
#include <set>
#include <stdexcept>

HandsModel::HandsModel(const Json::Value& json)
{
	LoadPlayerNames(json["playerNames"]);
	LoadHands(json["hands"]);
}

const std::vector<std::string>& HandsModel::GetPlayerNames() const
{
	return playerNames;
}

const std::vector<HandModel>& HandsModel::GetHands() const
{
	return hands;
}

void HandsModel::LoadPlayerNames(const Json::Value& json)
{
	std::set<std::string> uniquePlayerNames;
	for (auto playerNameJson : json)
	{
		auto playerName = playerNameJson.asString();
		playerNames.push_back(playerName);
		uniquePlayerNames.insert(String::ToLower(playerName));
	}
	if (playerNames.size() != uniquePlayerNames.size())
		throw std::runtime_error("Players names in game must be unique.");
	if (playerNames.size() < 5)
		throw std::runtime_error("Game must have at least 5 players.");
}

void HandsModel::LoadHands(const Json::Value& json)
{
	for (auto handJson : json)
	{
		HandModel hand { handJson };
		auto maxPlayerIndex = playerNames.size() - 1;
		hand.Validate(maxPlayerIndex);
		hands.push_back(hand);
	}
	if (hands.empty())
		throw std::runtime_error("Game must have at least one hand.");
}

