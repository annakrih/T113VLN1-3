Create table IF NOT EXISTS Person_Gender(
id INTEGER PRIMARY KEY AUTOINCREMENT,
genderName TEXT NOT NULL,
genderChar TEXT
);

Create Table IF NOT EXISTS Person_nationality(
id INTEGER PRIMARY KEY AUTOINCREMENT,
countryCode TEXT NOT NULL,
countryName TEXT
);

Create table IF NOT EXISTS Person(
id INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL,
genderId INTEGER NOT NULL,
nationalityId INTEGER NOT NULL,
birthYear INTEGER NOT NULL,
deathYear INTEGER,
image BLOB,
FOREIGN KEY(genderId) REFERENCES Person_Gender(id),
FOREIGN KEY(nationalityId) REFERENCES Person_nationality(id)
);

Create table IF NOT EXISTS Computer_Type(
id INTEGER PRIMARY KEY AUTOINCREMENT,
typeName TEXT NOT NULL
);

Create table IF NOT EXISTS Computer(
id INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL,
typeId INTEGER NOT NULL,
designYear INTEGER,
buildYear INTEGER,
FOREIGN KEY(typeId) REFERENCES Computer_Type(id)
);

Create table IF NOT EXISTS Person_Computer(
id INTEGER PRIMARY KEY AUTOINCREMENT,
personId INTEGER NOT NULL,
computerId INTEGER NOT NULL,
FOREIGN KEY(personId) REFERENCES Person(id),
FOREIGN KEY(computerId) REFERENCES Computer(id)
);
