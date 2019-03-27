/*
 * Create-script voor Muziekdatabase
 * Firebird 2.5, versie 13-05-2016
 */

create table Muziekschool
(code            varchar(3)     not null,
 naam            varchar(30)    not null,
 plaats          varchar(20)    not null,
 primary key (code),
 unique (naam)
);

create table Componist
(nr              integer        not null,
 naam            varchar(20)    not null,
 geboortedatum   date,
 school          varchar(3),
 primary key (nr),
 foreign key (school) references Muziekschool(code)
    on update cascade,
 unique (naam)
);

create table Genre
(naam            varchar(10)    not null,
 primary key (naam)
);

create table Niveau
(code            char(1)        not null,
 omschrijving    varchar(15)    not null,
 primary key (code),
 unique (omschrijving)
);

create table Stuk
(nr              integer        not null,
 componist       integer        not null,
 titel           varchar(20)    not null,
 origineel       integer,
 genre           varchar(10)    not null,
 niveau          char(1),
 speelduur       numeric(3,1),
 jaar            numeric(4)     not null,
 primary key (nr),
 unique (componist, titel),
 foreign key (componist) references Componist(nr)
    on update cascade,
 foreign key (genre) references Genre(naam)
    on update cascade,
 foreign key (niveau) references Niveau(code)
    on update cascade
);

alter table Stuk
add foreign key (origineel) references Stuk(nr)
       on update cascade;

create table Instrument
(naam            varchar(14)    not null,
 toonhoogte      varchar(7)     not null,
 primary key (naam, toonhoogte)
);

create table Bezettingsregel
(stuk            integer        not null,
 instrument      varchar(14)    not null,
 toonhoogte      varchar(7)     not null,
 aantal          integer        not null,
 primary key (stuk, instrument, toonhoogte),
 foreign key (stuk) references Stuk (nr)
    on delete cascade on update cascade,
 foreign key (instrument, toonhoogte)
    references Instrument (naam, toonhoogte)
    on update cascade
);

/*
 * Hoewel Instrument.toonhoogte conceptueel gezien niet verplicht is, is
 * de kolom toch 'not null' vanwege het feit dat de meeste rdbms'en
 * (zoals Oracle en ook Firebird) eisen dat elke primary key kolom
 * not null is ('Codd-relationaliteit'). Het is in Firebird wel toegstaan
 * een primary key met een optionele kolom te definiëren, maar in die kolom
 * mag dan niet expliciet een null worden ingevuld.
 * Voor 'geen toonhoogte' moet dus een lege string worden ingevuld.
 */
