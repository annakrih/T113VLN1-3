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

    //fetches person tableModel from data layer
    QSqlRelationalTableModel * getPersonModel(QString filter = "");

    //fetches computer tableModel from data layer
    QSqlRelationalTableModel * getComputerModel(QString filter = "");

    //fetches person relation tableModel from data layer
    QSqlQueryModel * getPersonRelationModel(QString filter = "");

    //fetches computer relation tableModel from data layer
    QSqlQueryModel * getComputerRelationModel(QString filter = "");

    //takes in a  model and passes it down to the Data layer, where its changes get submitted.
    QSqlRelationalTableModel * submitDatabaseChanges(QSqlRelationalTableModel* model);

    QSqlRelationalTableModel * searchPerson(QString searchInput);
    QSqlRelationalTableModel * searchPerson(QString searchInput, QString gender, QString BYfrom, QString BYto, QString DYfrom, QString DYto, QString nationality);

    //creates tailored search string for person.name, and returns a table of the result
    QSqlRelationalTableModel * searchPersonName(QString search);

    //creates tailored search string for person.genderId , and returns a table of the result (genderid as genderName)
    QSqlRelationalTableModel * searchPersonGender(int genderType);

    //creates tailored search string for person.nationality, and returns a table of the result
    QSqlRelationalTableModel * searchPersonNationality(QString search);

    //creates tailored search string for person.birthYear, and returns a table of the result (accepts "from" or "from to")
    QSqlRelationalTableModel * searchPersonBY(QString search);

    //creates tailored search string for person.deathYear, and returns a table of the result (accepts "from" or "from to")
    QSqlRelationalTableModel * searchPersonDY(QString search);



    //creates tailored search string for computer.name, and returns a table of the result
    QSqlRelationalTableModel * searchComputerName(QString search);

    //creates tailored search string for computer.type, and returns a table of the result (typeid as typeName)
    QSqlRelationalTableModel * searchComputerType(QString search);

    //creates tailored search string for computer.designYear, and returns a table of the result
    QSqlRelationalTableModel * searchComputerDY(QString search);

    //creates tailored search string for computer.builtYear, and returns a table of the result
    QSqlRelationalTableModel * searchComputerBY(QString search);

    //passes on personId and computerId to the data layer, creates relation
    void createPCRelation(int p, int c);
};

#endif // Domain_H
