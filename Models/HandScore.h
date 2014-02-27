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
		int primaryPlayerIndex;
		int secondaryPlayerIndex;
	} leasterScore;
	struct
	{
		int loserPlayerIndex;
	} misplayScore;
};

