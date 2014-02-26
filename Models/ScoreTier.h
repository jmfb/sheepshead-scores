#pragma once
#include <string>

enum class ScoreTier : short
{
	Schneider = 1,
	NoSchneider = 2,
	NoTricker = 3
};

ScoreTier ParseScoreTier(const std::string& value);

