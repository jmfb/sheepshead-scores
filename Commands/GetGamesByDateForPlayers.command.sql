select	game.id,
	game.playedWhen,
	player.name,
	gamePlayer.score
from	player
	inner join gamePlayer
	on	gamePlayer.playerId = player.id
	inner join game
	on	game.id = gamePlayer.gameId
where	player.name in ({0})
and	game.playedWhen >= {1}
and	game.playedWhen < {2}
order by game.playedWhen,
	game.id,
	player.name;
