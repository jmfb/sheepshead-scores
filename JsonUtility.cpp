#include "JsonUtility.h"
#include "StringUtility.h"

namespace Json
{

std::string EscapeJson(const std::string& value)
{
	return String::Replace(value, "\"", "\\\"");
}

}

