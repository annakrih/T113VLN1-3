#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include "data.h"

using namespace std;

//domain layer
class Domain
{
private:
    //declare data variable, to have access to lower layer.
    Data data;

    Utils utils;
public:
    Domain();

    //returns QMap of <"GenderName", id>
    QMap<QString, int> getAcceptedGenderName();
    //returns QMap of <"GenderChar", id>
    QMap<QString, int> getAcceptedGenderChar();
    //returns QMap of <"Typename", id>
    QMap<QString, int> getAcceptedComputerTypeName();

    QMap<QString, int> getAcceptedNationality();

    //fetches person tableModel from data layer
    QSqlRelationalTableModel * getPersonModel(QString filter = "");

    //fetches computer tableModel from data layer
    QSqlRelationalTableModel * getComputerModel(QString filter = "");

    //fetches person relation tableModel from data layer
    QSqlQueryModel * getPersonRelationModel(QString filter = "");

    //fetches computer relation tableModel from data layer
    QSqlQueryModel * getComputerRelationModel(QString filter = "");

    //passes a message down to data layer for deleting all instances in person table
    QSqlQueryModel * getDeletePersonTable();

    //passes a message down to data layer for deleting all instances in computer table
    QSqlQueryModel * getDeleteComputerTable();

    QSqlQueryModel * getDeleteRelationTable();

    //takes in a  model and passes it down to the Data layer, where its changes get submitted.
    QSqlRelationalTableModel * submitDatabaseChanges(QSqlRelationalTableModel* model);

    QSqlRelationalTableModel * searchPerson(QString searchInput);
    QSqlRelationalTableModel * searchPerson(QString searchInput, QString gender, QString BYfrom, QString BYto, QString DYfrom, QString DYto, QString nationality);

    QSqlRelationalTableModel * searchComputer(QString searchNameInput);
    QSqlRelationalTableModel * searchComputer(QString searchNameInput, QString DYfrom, QString DYto, QString BYfrom, QString BYto, QString type);


    //passes on personId and computerId to the data layer, creates relation
    void createPCRelation(int p, int c);

    //get css string
    QString getCssString();
};

#endif // Domain_H
