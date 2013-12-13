#pragma once
#include "FormData.h"
#include <string>
#include <vector>
#include <pqxx/pqxx>

class PlayerScoreModel
{
public:
	PlayerScoreModel();
	PlayerScoreModel(const std::string& name, int score);
	PlayerScoreModel(const PlayerScoreModel& rhs) = default;
	~PlayerScoreModel() = default;
	
	PlayerScoreModel& operator=(const PlayerScoreModel& rhs) = default;
	
	void SetName(const std::string& value);
	void SetScore(int value);
	
	const std::string& GetName() const;
	int GetScore() const;
	
	static PlayerScoreModel Load(pqxx::result::tuple& result, int nameIndex, int scoreIndex);
	static PlayerScoreModel Load(const FormData& formData, int number);
	
	static std::vector<PlayerScoreModel> LoadAll(pqxx::result& results, int nameIndex, int scoreIndex);
	static std::vector<PlayerScoreModel> LoadAll(const FormData& formData);
	
private:
	std::string name;
	int score;
};

