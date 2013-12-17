#pragma once
#include "PlayerScoreModel.h"
#include <string>
#include <vector>

class ReportModel
{
public:
	ReportModel();
	ReportModel(const ReportModel& rhs) = default;
	~ReportModel() = default;
	
	ReportModel& operator=(const ReportModel& rhs) = default;
	
	void SetTitle(const std::string& value);
	void AddPlayerScore(const PlayerScoreModel& value);
	void SetGameId(int value);

	const std::string& GetTitle() const;
	const std::vector<PlayerScoreModel>& GetPlayerScores() const;
	int GetPointSpread() const;
	bool CanDelete() const;
	int GetGameId() const;
	
private:
	std::string title;
	std::vector<PlayerScoreModel> playerScores;
	bool canDelete;
	int gameId;
};

