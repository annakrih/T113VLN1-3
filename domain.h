#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include "data.h"
#include "config.h"
#include "person.h"
#include "computer.h"

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

    QSqlRelationalTableModel * submitDatabaseChanges(QSqlRelationalTableModel* model);

};

#endif // Domain_H
