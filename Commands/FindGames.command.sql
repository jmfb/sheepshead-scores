select	id,
	playedWhen
from	game
order by playedWhen desc,
	id desc
limit	{0}
offset	{1};

