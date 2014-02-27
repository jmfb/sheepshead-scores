#include "HandType.h"
#include <stdexcept>

HandType ParseHandType(const std::string& value)
{
	if (value == "normal")
		return HandType::Normal;
	if (value == "leaster")
		return HandType::Leaster;
	if (value == "misplay")
		return HandType::Misplay;
	throw std::runtime_error("invalid handType: " + value);
}

