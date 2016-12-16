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

    //gets nationality list from database
    QMap<QString, int> getAcceptedNationality();

    //fetches person tableModel from data layer
    QSqlRelationalTableModel * getPersonModel(QString filter = "");

    //fetches computer tableModel from data layer
    QSqlRelationalTableModel * getComputerModel(QString filter = "");

    //fetches relation tableModel from data layer
    QSqlRelationalTableModel * getPCRelationModel();

    //passes a message down to data layer for deleting all instances in person table
    QSqlRelationalTableModel *deletePersonTable();

    //passes a message down to data layer for deleting all instances in computer table
    QSqlRelationalTableModel * deleteComputerTable();

    //passes a message down to data layer for deleting all instances in relation table
    QSqlRelationalTableModel * deleteRelationTable();

    //get next autoIncrement ID for added person/computer, we do this so we can give it a valid ID right away
    //this way we can add relation right away, without saving to the database first.
    int getNextAutoId(QString table);

    //takes in a  model and passes it down to the Data layer, where its changes are submitted.
    QSqlRelationalTableModel * submitDatabaseChanges(QSqlRelationalTableModel* model);

    //Calls datalayer to import default data to an empty database.
    void initializeData();

    //get css from stylesheet.css file
    QString getCssString();
};

#endif // Domain_H
