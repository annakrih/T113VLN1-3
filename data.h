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



using namespace std;

//data layer

class Data
{
private:
    Utils utils;

    //custom dir/file variables;
    const QString databaseDir = utils.workingDir+"database/";
    const QString schemaFile = databaseDir + "schema.sql";
    const QString initialPersons = databaseDir + "personsInitialData.csv";
    const QString initialComputers = databaseDir + "computersInitialData.csv";
    const QString initialRelations = databaseDir + "relationsInitialData.csv";

    //init database and locate db file;
    QSqlDatabase db;
    QString dbName = databaseDir + "team8.db";


public:
    //default constructor
    Data();

    void importSQL();

    //get tableModel of Person sql table, searchable with filter; (filter strings created in domain layer)
    QSqlRelationalTableModel* readPeopleFromDatabase(QString filter = "");

    //get tableModel of Computer sql table, searchable with filter; (filter strings created in domain layer)
    QSqlRelationalTableModel* readComputerFromDatabase(QString filter = "");

    //get tableModel of computer where person.id has a relation
    QSqlQueryModel* readPersonRelation(QString id);

    //get tableModel of person where person.id has a relation
    QSqlQueryModel* readComputerRelation(QString id);

    //submit any changes to table, QSqlRelationalTableModel deals with all inserts/deletes/updates needed. (awesome)
    QSqlRelationalTableModel* submitDatabaseChanges(QSqlRelationalTableModel* model);

    //gets the list of genders stored on the database, has both "M" and "Male" hence the double map.
    //domain has functions get either char or string.
    QMap<int,QMap<QString,QString>>getAcceptedGender();

    //gets the list of accepted computer types
    QMap<QString, int> getAcceptedComputerTypes();

    //takes in personId and computerId and creates a relation between the two tables;
    void createPCRelation(int p, int c);

    //function that import cvs files and their data to the database.
    void initializeData();
    void initializePersons();
    void initializeComputers();
    void initializeRelations();

};

#endif // DATA_H
