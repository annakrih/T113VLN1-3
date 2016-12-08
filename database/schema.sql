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

Insert into Person(name,genderId,nationality,birthYear,deathYear)
Values("TestMan",1,"Testland",1950,0);

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

Insert into Computer(name,typeId,designYear,buildYear)
Values("TestComp",2,2000,2010);
Insert into Computer(name,typeId,designYear,buildYear)
Values("Android",1,2016,2016);

Create table IF NOT EXISTS Person_Computer(
id INTEGER PRIMARY KEY AUTOINCREMENT,
personId INTEGER NOT NULL,
computerId INTEGER NOT NULL,
FOREIGN KEY(personId) REFERENCES Person(id),
FOREIGN KEY(computerId) REFERENCES Computer(id)
);

Insert into Person_Computer(personId,computerId)
Values(1,1);

Insert into Person_Computer(personId,computerId)
Values(1,2);
