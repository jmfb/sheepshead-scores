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

void CreateHand(SqlCommand& command, int gameId, const std::vector<int>& playerIds, const HandModel& hand)
{
	auto leadPlayerId = playerIds[hand.GetLeadPlayerIndex()];
	auto results = command.Execute(
		Commands::CreateHand,
		gameId,
		hand.GetDoubler(),
		static_cast<short>(hand.GetHandType()),
		leadPlayerId);
	auto handId = results[0][0].as<int>();
	for (auto playerIndex : hand.GetPlayerIndices())
		command.Execute(Commands::CreateHandPlayer, handId, playerIds[playerIndex]);
	switch(hand.GetHandType())
	{
	case HandType::Normal:
		command.Execute(
			Commands::CreateHandNormalScore,
			handId,
			hand.GetScore().normalScore.win,
			static_cast<short>(hand.GetScore().normalScore.scoreTier),
			playerIds[hand.GetScore().normalScore.pickerPlayerIndex],
			playerIds[hand.GetScore().normalScore.partnerPlayerIndex]);
		break;
	case HandType::Leaster:
		command.Execute(
			Commands::CreateHandLeasterScore,
			handId,
			playerIds[hand.GetScore().leasterScore.primaryPlayerIndex],
			playerIds[hand.GetScore().leasterScore.secondaryPlayerIndex]);
		break;
	case HandType::Misplay:
		command.Execute(
			Commands::CreateHandMisplayScore,
			handId,
			playerIds[hand.GetScore().misplayScore.loserPlayerIndex]);
		break;
	}
}

NameLookupModel DataBridge::LookupNames(const std::string& query)
{
	const auto maximumResults = 5;
	SqlCommand command;
	auto results = command.Execute(Commands::NameLookup, "%" + query + "%", maximumResults);
	NameLookupModel model;
	for (auto result : results)
		model.AddName(result[0].as<std::string>());
	return model;
}

ReportModel DataBridge::ReportHands(
	const std::string& date,
	const std::vector<std::string>& playerNames,
	const std::vector<HandModel>& hands)
{
	SqlCommand command;
	auto gameId = CreateGame(command, date);
	
	ReportModel report;
	report.SetTitle("New Scores for " + date + ".");

	std::vector<int> playerIds;
	std::vector<int> playerScores;
	for (auto playerName : playerNames)
	{
		auto playerId = FindOrCreatePlayer(command, playerName);
		playerIds.push_back(playerId);
		playerScores.push_back(0);
	}
	
	for (auto hand : hands)
		for (auto handScore : hand.GetScores())
			playerScores[handScore.GetPlayerIndex()] += handScore.GetScore();
	
	for (auto index = 0ul; index < playerIds.size(); ++index)
	{
		auto playerId = playerIds[index];
		auto playerScore = playerScores[index];
		UpdateGamePlayerScore(command, gameId, playerId, playerScore);
		report.AddPlayerScore({ playerNames[index], playerScore });
	}
	
	for (auto hand : hands)
		CreateHand(command, gameId, playerIds, hand);
	
	command.Commit();
	return report;
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

ReportModel DataBridge::ReportScoresSince(const std::string& since, const std::string& until, const std::string& title)
{
	SqlCommand command;
	auto results = command.Execute(Commands::ScoreReport, since, until);
	ReportModel report;
	report.SetTitle(title);
	auto playerScores = PlayerScoreModel::LoadAll(results, 0, 1);
	for (auto playerScore : playerScores)
		report.AddPlayerScore(playerScore);
	return report;
}

std::vector<PlayerGameModel> DataBridge::ReportPlayerGames(
	const std::string& player,
	const std::string& since,
	const std::string& until)
{
	std::vector<PlayerGameModel> models;
	SqlCommand command;
	auto results = command.Execute(Commands::ScoreReportPlayer, player, since, until);
	for (auto result : results)
		models.push_back({ result[0].as<std::string>(), result[1].as<int>() });
	return models;
}

ReportsModel DataBridge::FindGames(int skip, int take)
{
	SqlCommand command;
	ReportsModel reports;
	auto games = command.Execute(Commands::FindGames, take, skip);
	for (auto game : games)
	{
		ReportModel report;
		report.SetTitle("Scores for " + game[1].as<std::string>() + ".");
		auto gameId = game[0].as<int>();
		report.SetGameId(gameId);
		auto results = command.Execute(Commands::LoadGame, gameId);
		auto playerScores = PlayerScoreModel::LoadAll(results, 0, 1);
		for (auto playerScore : playerScores)
			report.AddPlayerScore(playerScore);
		reports.AddReport(report);
	}
	return reports;
}

void DataBridge::DeleteGame(int gameId)
{
	SqlCommand command;
	command.Execute(Commands::DeleteGame, gameId);
	command.Commit();
}

