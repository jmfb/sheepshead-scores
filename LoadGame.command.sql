select	player.name,
	gamePlayer.score
from	gamePlayer
	inner join player
	on	player.id = gamePlayer.playerId
where	gamePlayer.gameId = {0}
order by gamePlayer.score desc,
	player.name asc;

