select	game.playedWhen,
	gamePlayer.score
from	player
	inner join gamePlayer
	on	gamePlayer.playerId = player.id
	inner join game
	on	game.id = gamePlayer.gameId
where	player.name = {0}
and	game.playedWhen >= {1}
and	game.playedWhen < {2}
order by game.playedWhen desc,
	game.id desc;

