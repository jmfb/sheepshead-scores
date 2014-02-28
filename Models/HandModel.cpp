#include "HandModel.h"
#include <map>
#include <set>
#include <algorithm>
#include <stdexcept>

HandModel::HandModel(Json::Value& value)
{
	for (auto playerIndex : value["playerIndices"])
		playerIndices.push_back(playerIndex.asInt());
	doubler = value["doubler"].asBool();
	handType = ParseHandType(value["handType"].asString());
	leadPlayerIndex = value["leadPlayerIndex"].asInt();
	auto scoreValue = value["score"];
	switch(handType)
	{
	case HandType::Normal:
		score.normalScore.win = scoreValue["win"].asBool();
		score.normalScore.scoreTier = ParseScoreTier(scoreValue["scoreTier"].asString());
		score.normalScore.pickerPlayerIndex = scoreValue["pickerPlayerIndex"].asInt();
		score.normalScore.partnerPlayerIndex = scoreValue["partnerPlayerIndex"].asInt();
		break;
	case HandType::Leaster:
		{
			score.leasterScore.primaryPlayerIndex = scoreValue["primaryPlayerIndex"].asInt();
			auto secondaryPlayerIndex = scoreValue["secondaryPlayerIndex"];
			if (secondaryPlayerIndex.isNull())
				score.leasterScore.secondaryPlayerIndex = nullptr;
			else
				score.leasterScore.secondaryPlayerIndex = secondaryPlayerIndex.asInt();
		}
		break;
	case HandType::Misplay:
		score.misplayScore.loserPlayerIndex = scoreValue["loserPlayerIndex"].asInt();
		break;
	}
}

const std::vector<int>& HandModel::GetPlayerIndices() const
{
	return playerIndices;
}

bool HandModel::GetDoubler() const
{
	return doubler;
}

HandType HandModel::GetHandType() const
{
	return handType;
}

int HandModel::GetLeadPlayerIndex() const
{
	return leadPlayerIndex;
}

const HandScore& HandModel::GetScore() const
{
	return score;
}

void HandModel::Validate(int maxPlayerIndex) const
{
	if (playerIndices.size() != 5)
		throw std::runtime_error("A hand must have exactly 5 players.");
		
	std::set<int> uniquePlayerIndices;
	std::copy(
		playerIndices.begin(),
		playerIndices.end(),
		std::inserter(uniquePlayerIndices, uniquePlayerIndices.end()));
	if (uniquePlayerIndices.size() != 5)
		throw std::runtime_error("A hand must have exactly 5 distinct players.");
		
	for (auto playerIndex : playerIndices)
		ValidatePlayerIndex(playerIndex, maxPlayerIndex);
		
	ValidatePlayerInHand(leadPlayerIndex, "Lead player", maxPlayerIndex);
	
	switch(handType)
	{
	case HandType::Normal:
		ValidatePlayerInHand(score.normalScore.pickerPlayerIndex, "Picker", maxPlayerIndex);
		ValidatePlayerInHand(score.normalScore.partnerPlayerIndex, "Partner", maxPlayerIndex);
		break;
	case HandType::Leaster:
		ValidatePlayerInHand(score.leasterScore.primaryPlayerIndex, "Primary", maxPlayerIndex);
		if (score.leasterScore.secondaryPlayerIndex != nullptr)
			ValidatePlayerInHand(score.leasterScore.secondaryPlayerIndex.GetValue(), "Secondary", maxPlayerIndex);
		break;
	case HandType::Misplay:
		ValidatePlayerInHand(score.misplayScore.loserPlayerIndex, "Loser", maxPlayerIndex);
		break;
	}
}

std::vector<HandScoreModel> HandModel::GetScores() const
{
	std::map<int, int> scores;
	switch(handType)
	{
	case HandType::Normal:
		{
			auto increment = static_cast<int>(score.normalScore.scoreTier) * (score.normalScore.win ? 1 : -2);
			for (auto playerIndex : playerIndices)
				scores[playerIndex] = (
					playerIndex == score.normalScore.pickerPlayerIndex &&
					playerIndex == score.normalScore.partnerPlayerIndex ? 4 * increment :
					playerIndex == score.normalScore.pickerPlayerIndex ? 2 * increment :
					playerIndex == score.normalScore.partnerPlayerIndex ? increment : -increment);
		}
		break;
	case HandType::Leaster:
		for (auto playerIndex : playerIndices)
			scores[playerIndex] = (
				playerIndex == score.leasterScore.primaryPlayerIndex &&
				score.leasterScore.secondaryPlayerIndex == nullptr ? 4 :
				playerIndex == score.leasterScore.primaryPlayerIndex ? 2 :
				score.leasterScore.secondaryPlayerIndex != nullptr &&
				playerIndex == score.leasterScore.secondaryPlayerIndex.GetValue() ? 1 : -1);
		break;
	case HandType::Misplay:
		for (auto playerIndex : playerIndices)
			scores[playerIndex] = (playerIndex == score.misplayScore.loserPlayerIndex ? -4 : 1);
		break;
	}
	
	std::vector<HandScoreModel> scoreModels;
	for (auto pair : scores)
		scoreModels.push_back({ pair.first, (doubler ? 2 : 1) * pair.second });
	return scoreModels;
}

void HandModel::ValidatePlayerIndex(int playerIndex, int maxPlayerIndex) const
{
	if (playerIndex < 0)
		throw std::runtime_error("Player index cannot be negative.");
	if (playerIndex > maxPlayerIndex)
		throw std::runtime_error("Player index was greater than allowed.");
}

void HandModel::ValidatePlayerInHand(
	int playerIndex,
	const std::string& playerPosition,
	int maxPlayerIndex) const
{
	ValidatePlayerIndex(playerIndex, maxPlayerIndex);
	if (std::find(playerIndices.begin(), playerIndices.end(), playerIndex) == playerIndices.end())
		throw std::runtime_error(playerPosition + " must be in the hand.");
}

