select	name
from	player
where	lower(name)
like	{0}
order by name
limit	{1};

