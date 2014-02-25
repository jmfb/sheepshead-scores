#include "Debug.h"

Debug& Debug::GetInstance()
{
	static Debug instance;
	return instance;
}

void Debug::Write(const std::string& message)
{
	messages.push_back(message);
}

bool Debug::HasMessages() const
{
	return !messages.empty();
}

const std::vector<std::string>& Debug::GetMessages() const
{
	return messages;
}

