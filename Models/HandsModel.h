#pragma once
#include <vector>
#include <string>
#include "HandModel.h"
#include "json/value.h"

class HandsModel
{
public:
	HandsModel() = default;
	HandsModel(const Json::Value& json);
	HandsModel(const HandsModel& rhs) = default;
	~HandsModel() = default;
	
	HandsModel& operator=(const HandsModel& rhs) = default;

	const std::vector<std::string>& GetPlayerNames() const;
	const std::vector<HandModel>& GetHands() const;
	
private:
	void LoadPlayerNames(const Json::Value& json);
	void LoadHands(const Json::Value& json);

private:
	std::vector<std::string> playerNames;
	std::vector<HandModel> hands;
};

