#include "ScoreTier.h"
#include <stdexcept>

ScoreTier ParseScoreTier(const std::string& value)
{
	if (value == "schneider")
		return ScoreTier::Schneider;
	if (value == "noSchneider")
		return ScoreTier::NoSchneider;
	if (value == "noTricker")
		return ScoreTier::NoTricker;
	throw std::runtime_error("invalid scoreTier: " + value);
}

