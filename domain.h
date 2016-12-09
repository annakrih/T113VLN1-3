#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include "data.h"
#include "config.h"

using namespace std;

//domain layer
class Domain
{
private:
    //declare data variable, to have access to lower layer.
    Data data;
    static const int dummyNull = 9999;
public:
    Domain();

    //Function that uses data.clearPersonInDatabase to clear everything in the list.
    void clearPerson();

    //gets config from data layer
    Config getConfig();

    //passes on a Confic object to overrwrite the current config
    void setConfig(Config c);

    QMap<QString, int> getAcceptedGenderName();
    QMap<QString, int> getAcceptedGenderChar();
    QMap<int, QString> getAcceptedComputerTypeName();

    QSqlRelationalTableModel * getPersonModel(QString filter = "");

    QSqlRelationalTableModel * getComputerModel(QString filter = "");

    QSqlQueryModel * getPersonRelationModel(QString filter = "");

    QSqlQueryModel * getComputerRelationModel(QString filter = "");

    QSqlRelationalTableModel * submitDatabaseChanges(QSqlRelationalTableModel* model);



    QSqlRelationalTableModel * searchPersonName(QString search);

    QSqlRelationalTableModel * searchPersonGender(QString search);

    QSqlRelationalTableModel * searchPersonNationality(QString search);

    QSqlRelationalTableModel * searchPersonBY(QString search);

    QSqlRelationalTableModel * searchPersonDY(QString search);



    QSqlRelationalTableModel * searchComputerName(QString search);

    QSqlRelationalTableModel * searchComputerType(QString search);

    QSqlRelationalTableModel * searchComputerDY(QString search);

    QSqlRelationalTableModel * searchComputerBY(QString search);
};

#endif // Domain_H
