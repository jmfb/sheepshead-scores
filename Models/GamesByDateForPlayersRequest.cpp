#include "GamesByDateForPlayersRequest.h"
#include "DateUtility.h"

GamesByDateForPlayersRequest::GamesByDateForPlayersRequest(const Json::Value& json)
{
	auto playerNameValues = json["playerNames"];
	for (auto playerNameValue : playerNameValues)
		playerNames.push_back(playerNameValue.asString());
	auto period = json["period"].asString();
	periodStart = Date::GetBeginningOfPeriod(period);
	periodEnd = Date::GetEndOfPeriod(period);
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
