Create table IF NOT EXISTS Person(
id INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL,
gender TEXT NOT NULL,
birthYear INTEGER NOT NULL,
deathYear INTEGER,
nationality TEXT NOT NULL
);

Create table IF NOT EXISTS Computer_Type(
id INTEGER PRIMARY KEY AUTOINCREMENT,
type_name TEXT NOT NULL
);

Create table IF NOT EXISTS Computer(
id INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL,
designYear INTEGER,
buildYear INTEGER,
type INTEGER NOT NULL,
FOREIGN KEY(type) REFERENCES Computer_Type(id)
);

Create table IF NOT EXISTS PersonComputer(
id INTEGER PRIMARY KEY AUTOINCREMENT,
personId INTEGER NOT NULL,
computerId INTEGER NOT NULL,
FOREIGN KEY(personId) REFERENCES Person(id),
FOREIGN KEY(computerId) REFERENCES Computer(id)
)