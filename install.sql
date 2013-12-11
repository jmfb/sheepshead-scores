create table player
(
	id serial not null,
	name varchar(100) not null,
	constraint pk_player primary key (id),
	constraint u_player_name unique (name)
);

create table game
(
	id serial not null,
	playedWhen date not null,
	constraint pk_game primary key (id),
	constraint u_game_date unique (playedWhen)
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

