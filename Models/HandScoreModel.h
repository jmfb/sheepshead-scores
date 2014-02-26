#pragma once

class HandScoreModel
{
public:
	HandScoreModel();
	HandScoreModel(int playerIndex, int score);
	HandScoreModel(const HandScoreModel& rhs) = default;
	~HandScoreModel() = default;
	
	HandScoreModel& operator=(const HandScoreModel& rhs) = default;
	
	int GetPlayerIndex() const;
	int GetScore() const;
	
private:
	int playerIndex;
	int score;
};

