#pragma once
#include "Nullable.h"

struct HandScore
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
		Nullable<int> secondaryPlayerIndex;
	} leasterScore;
	struct
	{
		int loserPlayerIndex;
	} misplayScore;
};

