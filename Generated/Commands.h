#pragma once
#include <string>

namespace Commands
{
	const std::string CreateGame =
		"insert into game (\n"
		"	playedwhen\n"
		") values (\n"
		"	{0}\n"
		")\n"
		"returning id;\n";
	const std::string CreateGamePlayer =
		"insert into gamePlayer (\n"
		"	gameId,\n"
		"	playerId,\n"
		"	score,\n"
		"	seatingOrder\n"
		")\n"
		"select	{0},\n"
		"	{1},\n"
		"	{2},\n"
		"	coalesce(max(seatingOrder) + 1, 0)\n"
		"from	gamePlayer\n"
		"where	gameId = {0}\n"
		"and	seatingOrder is not null;\n";
	const std::string CreateHand =
		"insert into hand (\n"
		"	gameId,\n"
		"	doubler,\n"
		"	handType,\n"
		"	leadPlayerid\n"
		") values (\n"
		"	{0},\n"
		"	{1},\n"
		"	{2},\n"
		"	{3}\n"
		")\n"
		"returning id;\n";
	const std::string CreateHandLeasterScore =
		"insert into handLeasterScore (\n"
		"	handId,\n"
		"	winnerPlayerId\n"
		") values (\n"
		"	{0},\n"
		"	{1}\n"
		");\n";
	const std::string CreateHandMisplayScore =
		"insert into handMisplayScore (\n"
		"	handId,\n"
		"	loserPlayerId\n"
		") values (\n"
		"	{0},\n"
		"	{1}\n"
		");\n";
	const std::string CreateHandNormalScore =
		"insert into handNormalScore (\n"
		"	handId,\n"
		"	win,\n"
		"	scoreTier,\n"
		"	pickerPlayerId,\n"
		"	partnerPlayerId\n"
		") values (\n"
		"	{0},\n"
		"	{1},\n"
		"	{2},\n"
		"	{3},\n"
		"	{4}\n"
		");\n";
	const std::string CreateHandPlayer =
		"insert into handPlayer (\n"
		"	handId,\n"
		"	playerId\n"
		") values (\n"
		"	{0},\n"
		"	{1}\n"
		");\n";
	const std::string CreateHandTiedLeasterScore =
		"insert into handTiedLeasterScore (\n"
		"	handId,\n"
		"	primaryPlayerId,\n"
		"	secondaryPlayerId\n"
		") values (\n"
		"	{0},\n"
		"	{1},\n"
		"	{2}\n"
		");\n";
	const std::string CreatePlayer =
		"insert into player (\n"
		"	name\n"
		") values (\n"
		"	{0}\n"
		")\n"
		"returning id;\n";
	const std::string DeleteGame =
		"delete	from handMisplayScore\n"
		"using	hand\n"
		"where	handId = hand.id\n"
		"and	hand.gameId = {0};\n"
		"delete	from handTiedLeasterScore\n"
		"using	hand\n"
		"where	handId = hand.id\n"
		"and	hand.gameId = {0};\n"
		"delete	from handLeasterScore\n"
		"using	hand\n"
		"where	handId = hand.id\n"
		"and	hand.gameId = {0};\n"
		"delete	from handNormalScore\n"
		"using	hand\n"
		"where	handId = hand.id\n"
		"and	hand.gameId = {0};\n"
		"delete	from handPlayer\n"
		"using	hand\n"
		"where	handId = hand.id\n"
		"and	hand.gameId = {0};\n"
		"delete	from hand\n"
		"where	gameId = {0};\n"
		"delete	from gamePlayer\n"
		"where	gameId = {0};\n"
		"delete	from game\n"
		"where	id = {0};\n";
	const std::string FindGamePlayer =
		"select	score\n"
		"from	gamePlayer\n"
		"where	gameId = {0}\n"
		"and	playerId = {1};\n";
	const std::string FindGames =
		"select	id,\n"
		"	playedWhen\n"
		"from	game\n"
		"order by playedWhen desc,\n"
		"	id desc\n"
		"limit	{0}\n"
		"offset	{1};\n";
	const std::string FindPlayer =
		"select	id\n"
		"from	player\n"
		"where	lower(name) = lower({0});\n";
	const std::string LoadGame =
		"select	player.name,\n"
		"	gamePlayer.score\n"
		"from	gamePlayer\n"
		"	inner join player\n"
		"	on	player.id = gamePlayer.playerId\n"
		"where	gamePlayer.gameId = {0}\n"
		"order by gamePlayer.score desc,\n"
		"	player.name asc;\n";
	const std::string NameLookup =
		"select	name\n"
		"from	player\n"
		"where	lower(name)\n"
		"like	lower({0})\n"
		"order by name\n"
		"limit	{1};\n";
	const std::string ScoreReport =
		"select	player.name,\n"
		"	sum(gamePlayer.score)\n"
		"from	game\n"
		"	inner join gamePlayer\n"
		"	on	gamePlayer.gameId = game.id\n"
		"	inner join player\n"
		"	on	player.id = gamePlayer.playerId\n"
		"where	game.playedWhen >= {0}\n"
		"and	game.playedWhen < {1}\n"
		"group by player.name\n"
		"order by 2 desc,\n"
		"	1 asc;\n";
	const std::string ScoreReportPlayer =
		"select	game.playedWhen,\n"
		"	gamePlayer.score\n"
		"from	player\n"
		"	inner join gamePlayer\n"
		"	on	gamePlayer.playerId = player.id\n"
		"	inner join game\n"
		"	on	game.id = gamePlayer.gameId\n"
		"where	lower(player.name) = lower({0})\n"
		"and	game.playedWhen >= {1}\n"
		"and	game.playedWhen < {2}\n"
		"order by game.playedWhen desc,\n"
		"	game.id desc;\n";
	const std::string UpdateGamePlayer =
		"update	gamePlayer\n"
		"set	score = {0}\n"
		"where	gameId = {1}\n"
		"and	playerId = {2};\n";
}
