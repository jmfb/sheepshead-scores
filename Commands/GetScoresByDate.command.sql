select	player.name,
	sum(gamePlayer.score) as score
from	game
	inner join gamePlayer
	on	gamePlayer.gameId = game.id
	inner join player
	on	player.id = gamePlayer.playerId
where	game.playedWhen >= {0}
and	game.playedWhen < {1}
group by player.name
order by sum(gamePlayer.score) desc,
	player.name asc;
