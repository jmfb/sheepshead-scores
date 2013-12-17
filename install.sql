create table player
(
	id serial not null,
	name varchar(100) not null,
	constraint pk_player primary key (id),
	constraint u_player_name unique (name)
);

create unique index u_player_lower_name on player (lower(name) text_ops);

create table game
(
	id serial not null,
	playedWhen date not null,
	constraint pk_game primary key (id)
);

create table gamePlayer
(
	gameId int not null,
	playerId int not null,
	score int not null,
	constraint pk_gamePlayer primary key (gameId, playerId),
	constraint fk_gamePlayer_game foreign key (gameId) references game (id),
	constraint fk_gamePlayer_player foreign key (playerId) references player (id)
);

create table deletedGame
(
	id int not null,
	playedWhen date not null,
	constraint pk_deletedGame primary key (id)
);

create table deletedGamePlayer
(
	gameId int not null,
	playerId int not null,
	score int not null,
	constraint pk_deletedGamePlayer primary key (gameId, playerId),
	constraint fk_deletedGamePlayer_deletedGame foreign key (gameId) references deletedGame (id),
	constraint fk_deletedGamePlayer_player foreign key (playerId) references player (id)
);

