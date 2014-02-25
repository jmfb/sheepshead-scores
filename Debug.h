#pragma once
#include <vector>
#include <string>

class Debug
{
private:
	Debug() = default;
	Debug(const Debug& rhs) = delete;
	~Debug() = default;
	
	Debug& operator=(const Debug& rhs) = default;

public:
	static Debug& GetInstance();

	void Write(const std::string& message);
	bool HasMessages() const;
	const std::vector<std::string>& GetMessages() const;

private:
	std::vector<std::string> messages;
};

