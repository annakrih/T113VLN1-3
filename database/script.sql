Create table IF NOT EXISTS Person(
Id INTEGER PRIMARY KEY AUTOINCREMENT,
Name text NOT NULL,
Gender text NOT NULL,
BirthYear integer NOT NULL,
DeathYear integer,
Nationality text NOT NULL
);

Create table IF NOT EXISTS Computer(
Id INTEGER PRIMARY KEY AUTOINCREMENT,
Name text NOT NULL,
DesignYear integer,
BuildYear integer,
Type text NOT NULL
);

Create table IF NOT EXISTS PersonComputer(
ID INTEGER PRIMARY KEY AUTOINCREMENT,
PersonId integer NOT NULL,
ComputerId integer NOT NULL,
FOREIGN KEY(PersonId) REFERENCES Person(Id),
FOREIGN KEY(ComputerId) REFERENCES Computer(Id)
)
