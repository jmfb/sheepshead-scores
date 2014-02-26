delete	from handMisplayScore
using	hand
where	handId = hand.id
and	hand.gameId = {0};

delete	from handTiedLeasterScore
using	hand
where	handId = hand.id
and	hand.gameId = {0};

delete	from handLeasterScore
using	hand
where	handId = hand.id
and	hand.gameId = {0};

delete	from handNormalScore
using	hand
where	handId = hand.id
and	hand.gameId = {0};

delete	from handPlayer
using	hand
where	handId = hand.id
and	hand.gameId = {0};

delete	from hand
where	gameId = {0};

delete	from gamePlayer
where	gameId = {0};

delete	from game
where	id = {0};

