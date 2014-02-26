insert into gamePlayer (
	gameId,
	playerId,
	score,
	seatingOrder
)
select	{0},
	{1},
	{2},
	coalesce(max(seatingOrder) + 1, 0)
from	gamePlayer
where	gameId = {0}
and	seatingOrder is not null;

