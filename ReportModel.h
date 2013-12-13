#pragma once
#include "PlayerScoreModel.h"
#include <string>
#include <vector>

class ReportModel
{
public:
	ReportModel() = default;
	ReportModel(const ReportModel& rhs) = default;
	~ReportModel() = default;
	
	ReportModel& operator=(const ReportModel& rhs) = default;
	
	void SetTitle(const std::string& value);
	void AddPlayerScore(const PlayerScoreModel& value);

	const std::string& GetTitle() const;
	const std::vector<PlayerScoreModel>& GetPlayerScores() const;
	int GetPointSpread() const;
	
private:
	std::string title;
	std::vector<PlayerScoreModel> playerScores;
};

