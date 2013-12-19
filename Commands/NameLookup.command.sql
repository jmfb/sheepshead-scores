select	name
from	player
where	lower(name)
like	lower({0})
order by name
limit	{1};
