insert into deletedGame (
	id,
	playedWhen
)
select	id,
	playedWhen
from	game
where	id = {0};

insert into deletedGamePlayer (
	gameId,
	playerId,
	score
)
select	gameId,
	playerId,
	score
from	gamePlayer
where	gameId = {0};

delete	from gamePlayer
where	gameId = {0};

delete	from game
where	id = {0};

