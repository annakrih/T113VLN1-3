#ifndef DATA_H
#define DATA_H

#include <vector>
#include <QtSql>
#include <QCoreApplication>
#include <QVariant>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "config.h"
#include "person.h"
#include "computer.h"
#include "utils.h"



using namespace std;

//data layer

class Data
{
private:
    Utils utils;
    const QString databaseDir = utils.workingDir+"database/";
    const QString schemaFile = databaseDir + "schema.sql";
    //vector contains the list of people
    vector<Person> personList;
    vector<Computer> compList;

    QSqlDatabase db;
    QString dbName = databaseDir + "team8.db";

    //people file path
    const QString peopleFile = databaseDir+"people.txt";
    //config file path
    const QString configFile = databaseDir+"config.txt";

    //confic class contains config settings.
    Config config;


public:
    //default constructor
    Data();

    void importSQL();

    //getList returns main person list
    vector<Person> getPersonList();

    //getcomputerlist returns the list of computers
    vector<Computer> getComputerList();

    //writePersonTofile takes a person class as parameter, and adds it to both the main person vector, and people.txt file
    void writePersonToDatabase(Person P, bool push = 1);

    //
    void writeComputerToDatabase(Computer c, bool push = 1);

    //reads information stored inside a file and puts it into the main person vector
    QSqlRelationalTableModel* readPeopleFromDatabase();

    QSqlRelationalTableModel* submitDatabaseChanges(QSqlRelationalTableModel* model);

    //reads info stored inside a file and puts it into the main computer vector
    void readComputerFromDatabase();

    //removePersonFromDatabase takes a person as variable, if identical person exists in the database, it is removed from both main vector and people.txt
    void removePersonFromDatabase(Person personToRemove);

    void clearDatabase();

    //overwrites data in people.txt
    void rewriteDatabase();

    //editPersonInDatabase takes a person as variable, if identical person exists in the database, it is overwritten in both main vector and people.txt
    void editPersonInDatabase(Person personToEdit);

    //Clears everything from the list
    //drops table, essentially
    void clearPersonInDataBase();

    //swapPersonsInDatabase overwrites originalPerson with newPerson
    void swapPersonsInDatabase(Person& originalP, Person& newP);

    //readConfigFromFile reads saved settings from config.txt, and puts them in Data.config for easy access
    void readConfigFromFile();

    //writeConfigToFile overwrites config.txt with new settings.
    void writeConfigToFile(Config c);

    //getConfig makes config settings accessable in other layers, returns copy of config.
    Config getConfig();

    QMap<int,QMap<QString,QString>> getAcceptedGender();
};

#endif // DATA_H
