#pragma once

union HandScore
{
	struct
	{
		bool win;
		ScoreTier scoreTier;
		int pickerPlayerIndex;
		int partnerPlayerIndex;
	} normalScore;
	struct
	{
		int winnerPlayerIndex;
	} leasterScore;
	struct
	{
		int primaryPlayerIndex;
		int secondaryPlayerIndex;
	} tiedLeasterScore;
	struct
	{
		int loserPlayerIndex;
	} misplayScore;
};

