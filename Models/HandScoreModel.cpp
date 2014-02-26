#include "HandScoreModel.h"

HandScoreModel::HandScoreModel()
	: playerIndex(0), score(0)
{
}

HandScoreModel::HandScoreModel(int playerIndex, int score)
	: playerIndex(playerIndex), score(score)
{
}

int HandScoreModel::GetPlayerIndex() const
{
	return playerIndex;
}

int HandScoreModel::GetScore() const
{
	return score;
}

