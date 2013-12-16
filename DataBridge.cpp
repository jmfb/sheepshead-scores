#include "DataBridge.h"
#include "SqlCommand.h"
#include "Commands.h"
#include "StringUtility.h"

int CreateGame(SqlCommand& command, const std::string& date)
{
	auto results = command.Execute(Commands::CreateGame, date);
	return results[0][0].as<int>();
}

int FindOrCreatePlayer(SqlCommand& command, const std::string& name)
{
	auto results = command.Execute(Commands::FindPlayer, name);
	if (results.empty())
		results = command.Execute(Commands::CreatePlayer, name);
	return results[0][0].as<int>();
}

void UpdateGamePlayerScore(SqlCommand& command, int gameId, int playerId, int score)
{
	auto results = command.Execute(Commands::FindGamePlayer, gameId, playerId);
	if (results.empty())
		command.Execute(Commands::CreateGamePlayer, gameId, playerId, score);
	else
		command.Execute(Commands::UpdateGamePlayer, score + results[0][0].as<int>(), gameId, playerId);
}

NameLookupModel DataBridge::LookupNames(const std::string& query)
{
	const auto maximumResults = 5;
	SqlCommand command;
	auto results = command.Execute(Commands::NameLookup, "%" + String::ToLower(query) + "%", maximumResults);
	NameLookupModel model;
	for (auto result : results)
		model.AddName(result[0].as<std::string>());
	return model;
}

ReportModel DataBridge::ReportScores(const std::string& date, const std::vector<PlayerScoreModel>& playerScores)
{
	SqlCommand command;
	auto gameId = CreateGame(command, date);

	ReportModel report;
	report.SetTitle("New Scores for " + date + ".");

	for (auto playerScore : playerScores)
	{
		report.AddPlayerScore(playerScore);
		auto playerId = FindOrCreatePlayer(command, playerScore.GetName());
		UpdateGamePlayerScore(command, gameId, playerId, playerScore.GetScore());
	}
	
	command.Commit();
	return report;
}

ReportModel DataBridge::ReportScoresSince(const std::string& since, const std::string& title)
{
	SqlCommand command;
	auto results = command.Execute(Commands::ScoreReport, since);
	ReportModel report;
	report.SetTitle(title);
	auto playerScores = PlayerScoreModel::LoadAll(results, 0, 1);
	for (auto playerScore : playerScores)
		report.AddPlayerScore(playerScore);
	return report;
}

