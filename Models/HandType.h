#pragma once
#include <string>

enum class HandType : short
{
	Normal = 1,
	Leaster = 2,
	TiedLeaster = 3,
	Misplay = 4
};

HandType ParseHandType(const std::string& value);

