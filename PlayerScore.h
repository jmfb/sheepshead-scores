#pragma once
#include "FormData.h"
#include <string>
#include <vector>
#include <pqxx/pqxx>

class PlayerScore
{
public:
	PlayerScore();
	PlayerScore(const std::string& name, int score);
	PlayerScore(const PlayerScore& rhs) = default;
	~PlayerScore() = default;
	
	PlayerScore& operator=(const PlayerScore& rhs) = default;
	
	void SetName(const std::string& value);
	void SetScore(int value);
	
	const std::string& GetName() const;
	int GetScore() const;
	
	static PlayerScore Load(pqxx::result::tuple& result, int nameIndex, int scoreIndex);
	static PlayerScore Load(const FormData& formData, int number);
	
	static std::vector<PlayerScore> LoadAll(pqxx::result& results, int nameIndex, int scoreIndex);
	static std::vector<PlayerScore> LoadAll(const FormData& formData);
	
private:
	std::string name;
	int score;
};

