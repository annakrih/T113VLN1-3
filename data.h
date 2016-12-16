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
#include "utils.h"
#include <QApplication>

using namespace std;

//data layer

class Data
{
private:
    Utils utils;

    //custom dir/file variables;
    const QString databaseDir = utils.workingDir+"database/";
    const QString schemaFile = databaseDir + "schema.sql";
    const QString initialGender = databaseDir + "genderInitialData.csv";
    const QString initialNationality = databaseDir + "nationalityInitialData.csv";
    const QString initialPerson = databaseDir + "personInitialData.csv";
    const QString initialComputerType = databaseDir + "computerTypeInitialData.csv";
    const QString initialComputer = databaseDir + "computerInitialData.csv";
    const QString initialPerson_Computer = databaseDir + "relationInitialData.csv";


    //init database and locate db file;
    QSqlDatabase db;
    QString dbName = databaseDir + "team8.db";

public:
    //default constructor
    Data();

    //functions to import default database if team8.db is deleted
    void importSchema();
    void importCSV(QString tableName, QFile &csvFile);

    //import from css file
    QString importCss();

    //get tableModel of Person sql table, searchable with filter; (filter strings created in domain layer)
    QSqlRelationalTableModel* readPeopleFromDatabase(QString filter = "");

    //get tableModel of Computer sql table, searchable with filter; (filter strings created in domain layer)
    QSqlRelationalTableModel* readComputerFromDatabase(QString filter = "");

    //get tableModel of relation table between computerrs and persons
    QSqlRelationalTableModel* readPCRelationFromDatabase();

    //Functioning to delete all instances of Persons, Computers and Relations:
    QSqlRelationalTableModel *deleteAllPersons();
    QSqlRelationalTableModel* deleteAllComputers();
    QSqlRelationalTableModel* deleteAllRelations();

    int getNextAutoId(QString table);

    //submit any changes to table, QSqlRelationalTableModel deals with all inserts/deletes/updates needed. (awesome)
    QSqlRelationalTableModel* submitDatabaseChanges(QSqlRelationalTableModel* model);

    //gets the list of genders stored on the database, has both "M" and "Male" hence the double map.
    //domain has functions get either char or string.
    QMap<int,QMap<QString,QString>>getAcceptedGender();

    //gets the list of accepted computer types
    QMap<QString, int> getAcceptedComputerTypes();

    QMap<QString, int> getAcceptedNationality();

    //takes in personId and computerId and creates a relation between the two tables;
    void createPCRelation(int p, int c);

    //function that import cvs files and their data to the database.
    void initializeDataTypes();
    void initializeData();
    void initializePersons();
    void initializeComputers();
    void initializeRelations();
};

#endif // DATA_H
