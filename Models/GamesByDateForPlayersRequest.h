#pragma once
#include "json/value.h"

class GamesByDateForPlayersRequest
{
public:
	GamesByDateForPlayersRequest(const Json::Value& json);
	GamesByDateForPlayersRequest(const GamesByDateForPlayersRequest& rhs) = default;
	~GamesByDateForPlayersRequest() = default;

	GamesByDateForPlayersRequest& operator=(const GamesByDateForPlayersRequest& rhs) = default;

	const std::vector<std::string>& GetPlayerNames() const;
	const std::string& GetPeriodStart() const;
	const std::string& GetPeriodEnd() const;

private:
	std::vector<std::string> playerNames;
	std::string periodStart;
	std::string periodEnd;
};
