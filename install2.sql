alter table gamePlayer add seatingOrder int null;

drop table deletedGamePlayer;

drop table deletedGame;

create table handScoreType
(
	handType smallint not null,
	description varchar(100) not null,
	constraint pk_handScoreType primary key (handType),
	constraint u_handScoreType_description unique (description)
);

insert into handScoreType (handType, description) values (1, 'normal');
insert into handScoreType (handType, description) values (2, 'leaster');
insert into handScoreType (handType, description) values (3, 'misplay');

create table hand
(
	id serial not null,
	gameId int not null,
	doubler boolean not null,
	handType smallint not null,
	leadPlayerId int not null,
	constraint pk_hand primary key (id),
	constraint fk_hand_gameId foreign key (gameId) references game (id),
	constraint fk_hand_handType foreign key (handType) references handScoreType (handType),
	constraint fk_hand_leadPlayerId foreign key (leadPlayerId) references player (id)
);

create index nu_hand_gameId on hand (gameId);

create table handPlayer
(
	handId int not null,
	playerId int not null,
	constraint pk_handPlayer primary key (handId, playerId),
	constraint fk_handPlayer_handId foreign key (handId) references hand (id),
	constraint fk_handPlayer_playerid foreign key (playerId) references player (id)
);

create index nu_handPlayer_playerId on handPlayer (playerId);

create table handScoreTier
(
	scoreTier smallint not null,
	description varchar(100) not null,
	constraint pk_handScoreTier primary key (scoreTier),
	constraint U_handScoreTier_description unique (description)
);

insert into handScoreTier (scoreTier, description) values (1, 'schneider');
insert into handScoreTier (scoreTier, description) values (2, 'no scheider');
insert into handScoreTier (scoreTier, description) values (3, 'no tricker');

create table handNormalScore
(
	handId int not null,
	win boolean not null,
	scoreTier smallint not null,
	pickerPlayerId int not null,
	partnerPlayerId int not null,
	constraint pk_handNormalScore primary key (handId),
	constraint fk_handNormalScore_handId foreign key (handId) references hand (id),
	constraint fk_handNormalScore_scoreTier foreign key (scoreTier) references handScoreTier (scoreTier),
	constraint fk_handNormalScore_pickerPlayerId foreign key (pickerPlayerId) references player (id),
	constraint fk_handNormalScore_partnerPlayerId foreign key (partnerPlayerId) references player (id)
);

create table handLeasterScore
(
	handId int not null,
	primaryPlayerId int not null,
	secondaryPlayerId int not null,
	constraint pk_handLeasterScore primary key (handId),
	constraint fk_handLeasterScore_handId foreign key (handId) references hand (id),
	constraint fk_handLeasterScore_primaryPlayerId foreign key (primaryPlayerId) references player (id),
	constraint fk_handLeasterScore_secondaryPlayerId foreign key (secondaryPlayerId) references player (id)
);

create table handMisplayScore
(
	handId int not null,
	loserPlayerId int not null,
	constraint pk_handMisplayScore primary key (handId),
	constraint fk_handMisplayScore_handId foreign key (handId) references hand (id),
	constraint fk_handMisplayScore_loserPlayerId foreign key (loserPlayerId) references player (id) 
);

