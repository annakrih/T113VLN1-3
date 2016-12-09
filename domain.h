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

    Utils utils;
public:
    Domain();

    QMap<QString, int> getAcceptedGenderName();
    QMap<QString, int> getAcceptedGenderChar();
    QMap<QString, int> getAcceptedComputerTypeName();

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

    void createPCRelation(int p, int c);
};

#endif // Domain_H
