#include "HtmlUtility.h"
#include "StringUtility.h"
#include <sstream>
#include <iomanip>

namespace Html
{

int HexValue(char digit)
{
	if (digit >= '0' && digit <= '9')
		return digit - '0';
	if (digit >= 'a' && digit <= 'f')
		return digit - 'a' + 10;
	if (digit >= 'A' && digit <= 'F')
		return digit - 'A' + 10;
	return 0;
}

char DecodeHexCharacter(std::string::const_iterator& iter, std::string::const_iterator end)
{
	if (iter == end)
		return ' ';
	auto upperDigit = *iter;
	++iter;
	if (iter == end)
		return ' ';
	auto lowerDigit = *iter;
	return static_cast<char>((HexValue(upperDigit) << 4) | HexValue(lowerDigit));
}

std::string UrlDecode(const std::string& value)
{
	std::ostringstream out;
	for (auto iter = value.begin(); iter != value.end(); ++iter)
	{
		if (*iter == '%')
		{
			++iter;
			out << DecodeHexCharacter(iter, value.end());
		}
		else if (*iter == '+')
		{
			out << ' ';
		}
		else
		{
			out << *iter;
		}
	}
	return out.str();
}

std::string UrlEncodeCharacter(char character)
{
	std::ostringstream out;
	out << "%" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(character);
	return out.str();
}

std::string UrlEncode(const std::string& value)
{
	auto url = String::Replace(value, "%", "%25");
	const std::string charactersToEncode = "!@#$%^&()+={}[]|\\:;',/?`";
	for (auto character : charactersToEncode)
		url = String::Replace(url, { 1, character }, UrlEncodeCharacter(character));
	url = String::Replace(url, " ", "+");
	return url;
}

std::string EscapeHtml(const std::string& value)
{
	auto html = value;
	html = String::Replace(html, "&", "&amp;");
	html = String::Replace(html, "<", "&lt;");
	html = String::Replace(html, ">", "&gt;");
	html = String::Replace(html, "\"", "&quot;");
	return html;	
}

std::string EscapeHtml(int value)
{
	return std::to_string(value);
}

}

