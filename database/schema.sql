Create table IF NOT EXISTS Person_Gender(
id INTEGER PRIMARY KEY AUTOINCREMENT,
genderName TEXT NOT NULL,
genderChar TEXT
);

Insert into Person_Gender(genderName,genderChar)
Values("Male","M");

Insert into Person_Gender(genderName,genderChar)
Values("Female","F");

Create table IF NOT EXISTS Person(
id INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL,
genderId INTEGER NOT NULL,
nationality TEXT NOT NULL,
birthYear INTEGER NOT NULL,
deathYear INTEGER,
FOREIGN KEY(genderId) REFERENCES Person_Gender(id)
);

Create table IF NOT EXISTS Computer_Type(
id INTEGER PRIMARY KEY AUTOINCREMENT,
typeName TEXT NOT NULL
);

Insert into Computer_Type(typeName)
Values("Sex Bot");
Insert into Computer_Type(typeName)
Values("Toaster");
Insert into Computer_Type(typeName)
Values("Mechanical");

Create table IF NOT EXISTS Computer(
id INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL,
typeId INTEGER NOT NULL,
designYear INTEGER,
buildYear INTEGER,
FOREIGN KEY(typeId) REFERENCES Computer_Type(id)
);

Create table IF NOT EXISTS PersonComputer(
id INTEGER PRIMARY KEY AUTOINCREMENT,
personId INTEGER NOT NULL,
computerId INTEGER NOT NULL,
FOREIGN KEY(personId) REFERENCES Person(id),
FOREIGN KEY(computerId) REFERENCES Computer(id)
)
