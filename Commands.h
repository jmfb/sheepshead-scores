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
		"	score\n"
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
	const std::string FindGame =
		"select	id\n"
		"from	game\n"
		"where	playedwhen = {0};\n";
	const std::string FindGamePlayer =
		"select	score\n"
		"from	gamePlayer\n"
		"where	gameId = {0}\n"
		"and	playerId = {1};\n";
	const std::string FindPlayer =
		"select	id\n"
		"from	player\n"
		"where	name = {0};\n";
	const std::string NameLookup =
		"select	name\n"
		"from	player\n"
		"where	name\n"
		"like	{0}\n"
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
		"group by player.name\n"
		"order by 2 desc,\n"
		"	1 asc;\n";
	const std::string UpdateGamePlayer =
		"update	gamePlayer\n"
		"set	score = {0}\n"
		"where	gameId = {1}\n"
		"and	playerId = {2};\n";
}
