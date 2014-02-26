#pragma once
#include <vector>
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
	const HandScore& GetScore() const;

	std::vector<HandScoreModel> GetScores() const;
	
private:
	std::vector<int> playerIndices;
	bool doubler;
	HandType handType;
	HandScore score;
};

