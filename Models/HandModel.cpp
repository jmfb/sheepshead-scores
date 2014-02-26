#include "HandModel.h"
#include <map>

HandModel::HandModel(Json::Value& value)
{
	for (auto playerIndex : value["playerIndices"])
		playerIndices.push_back(playerIndex.asInt());
	doubler = value["doubler"].asBool();
	handType = ParseHandType(value["handType"].asString());
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
		score.leasterScore.winnerPlayerIndex = scoreValue["winnerPlayerIndex"].asInt();
		break;
	case HandType::TiedLeaster:
		score.tiedLeasterScore.primaryPlayerIndex = scoreValue["primaryPlayerIndex"].asInt();
		score.tiedLeasterScore.secondaryPlayerIndex = scoreValue["secondaryPlayerIndex"].asInt();
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

const HandScore& HandModel::GetScore() const
{
	return score;
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
			scores[playerIndex] = (playerIndex == score.leasterScore.winnerPlayerIndex ? 4 : -1);
		break;
	case HandType::TiedLeaster:
		for (auto playerIndex : playerIndices)
			scores[playerIndex] = (
				playerIndex == score.tiedLeasterScore.primaryPlayerIndex ? 2 :
				playerIndex == score.tiedLeasterScore.secondaryPlayerIndex ? 1 : -1);
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

