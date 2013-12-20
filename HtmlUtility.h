#pragma once
#include <string>

namespace Html
{
	std::string UrlDecode(const std::string& value);
	std::string UrlEncode(const std::string& value);

	std::string EscapeHtml(const std::string& value);
	std::string EscapeHtml(int value);
}

