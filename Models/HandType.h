#pragma once
#include <string>

enum class HandType : short
{
	Normal = 1,
	Leaster = 2,
	Misplay = 3
};

HandType ParseHandType(const std::string& value);

