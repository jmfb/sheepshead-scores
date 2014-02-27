#pragma once
#include <vector>
#include <string>
#include "HandScoreModel.h"
#include "HandType.h"
#include "ScoreTier.h"
#include "HandScore.h"
#include "json/value.h"

class HandModel
{
public:
	HandModel() = default;
	HandModel(Json::Value& value);
	HandModel(const HandModel& rhs) = default;
	~HandModel() = default;
	
	HandModel& operator=(const HandModel& rhs) = default;

	const std::vector<int>& GetPlayerIndices() const;
	bool GetDoubler() const;
	HandType GetHandType() const;
	int GetLeadPlayerIndex() const;
	const HandScore& GetScore() const;

	void Validate(int maxPlayerIndex) const;
	std::vector<HandScoreModel> GetScores() const;

private:
	void ValidatePlayerIndex(int playerIndex, int maxPlayerIndex) const;
	void ValidatePlayerInHand(
		int playerIndex,
		const std::string& playerPosition,
		int maxPlayerIndex) const;

private:
	std::vector<int> playerIndices;
	bool doubler;
	HandType handType;
	int leadPlayerIndex;
	HandScore score;
};

