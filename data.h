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
#include "utils.h"



using namespace std;

//data layer

class Data
{
private:
    Utils utils;
    const QString databaseDir = utils.workingDir+"database/";
    const QString schemaFile = databaseDir + "schema.sql";

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

    //reads information stored inside a file and puts it into the main person vector
    QSqlRelationalTableModel* readPeopleFromDatabase(QString filter = "");

    QSqlRelationalTableModel* readComputerFromDatabase(QString filter = "");

    QSqlRelationalTableModel* submitDatabaseChanges(QSqlRelationalTableModel* model);

    void clearDatabase();

    //readConfigFromFile reads saved settings from config.txt, and puts them in Data.config for easy access
    void readConfigFromFile();

    //writeConfigToFile overwrites config.txt with new settings.
    void writeConfigToFile(Config c);

    //getConfig makes config settings accessable in other layers, returns copy of config.
    Config getConfig();

    QMap<int,QMap<QString,QString>> getAcceptedGender();

    QMap<int, QString> getAcceptedComputerTypes();

    //functiion if file is empty
    void initializeData();
};

#endif // DATA_H
