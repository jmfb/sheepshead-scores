#include "GamesByDateForPlayersRequest.h"
#include <sstream>

GamesByDateForPlayersRequest::GamesByDateForPlayersRequest(const Json::Value& json)
{
	auto playerNameValues = json["playerNames"];
	for (auto playerNameValue : playerNameValues)
		playerNames.push_back(playerNameValue.asString());
	auto period = json["period"].asString();
	std::istringstream in(period);
	auto year = 0;
	auto month = 0;
	char separator = ' ';
	in >> year >> separator >> month;
	if (year < 1900 || year > 3000)
		throw std::runtime_error("Invalid year in period.");
	if (month < 0 || month > 12)
		throw std::runtime_error("Invalid month in period.");
	if (month == 0)
	{
		periodStart = std::to_string(year) + "-01-01";
		periodEnd = std::to_string(year + 1) + "-01-01";
	}
	else
	{
		periodStart = std::to_string(year) + "-" + std::to_string(month) + "-01";
		if (month == 12)
			periodEnd = std::to_string(year + 1) + "-01-01";
		else
			periodEnd = std::to_string(year) + "-" + std::to_string(month + 1) + "-01";
	}
}

const std::vector<std::string>& GamesByDateForPlayersRequest::GetPlayerNames() const
{
	return playerNames;
}

const std::string& GamesByDateForPlayersRequest::GetPeriodStart() const
{
	return periodStart;
}

const std::string& GamesByDateForPlayersRequest::GetPeriodEnd() const
{
	return periodEnd;
}
