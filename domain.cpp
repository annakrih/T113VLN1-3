#include "domain.h"

using namespace std;

//domain layer
Domain::Domain()
{

}
QSqlRelationalTableModel* Domain::submitDatabaseChanges(QSqlRelationalTableModel* model)
{
    return data.submitDatabaseChanges(model);
}

QSqlRelationalTableModel * Domain::getPersonModel(QString filter)
{
    return data.readPeopleFromDatabase(filter);
}

QSqlQueryModel * Domain::getComputerRelationModel(QString filter)
{
    return data.readComputerRelation(filter);
}

QSqlQueryModel * Domain::getPersonRelationModel(QString filter)
{
    return data.readPersonRelation(filter);
}




QSqlRelationalTableModel * Domain::getComputerModel(QString filter)
{
    return data.readComputerFromDatabase(filter);
}

QMap<QString,int> Domain::getAcceptedGenderName()
{

    QMap<int,QMap<QString,QString>> genderList = data.getAcceptedGender();
    QMap<QString,int> gList;
    QMapIterator<int,QMap<QString,QString>> i(genderList);
    while (i.hasNext())
    {
        i.next();
        gList.insert(i.value().values().at(0),i.key());
    }
    return gList;
}

QMap<QString, int> Domain::getAcceptedGenderChar()
{

    QMap<int,QMap<QString,QString>> genderList = data.getAcceptedGender();
    QMap<QString,int> gList;
    QMapIterator<int,QMap<QString,QString>> i(genderList);
    while (i.hasNext())
    {
        i.next();
        gList.insert(i.value().values().at(1),i.key());
    }
    return gList;
}

QMap<int, QString> Domain::getAcceptedComputerTypeName()
{
    return data.getAcceptedComputerTypes();
}

//Gets the config object that holds the config settings from the data layer
Config Domain::getConfig()
{
    return data.getConfig();
}

//passes a config object to the data layer for processing
//overwrite old config
void Domain::setConfig(Config c)
{
    data.writeConfigToFile(c);
}

QSqlRelationalTableModel * Domain::searchPersonName(QString search)
{
    QString filter = "person.name like '%"+search+"%'";
    return data.readPeopleFromDatabase(filter);
}

QSqlRelationalTableModel * Domain::searchComputerName(QString search)
{
    QString filter = "computer.name like '%"+search+"%'";
    return data.readComputerFromDatabase(filter);
}

QSqlRelationalTableModel * Domain::searchComputerDY(QString search)
{
    QStringList designY = search.split(" ");

    QString filter;
    if(designY.size() == 2)
    {
        filter = "computer.designYear > "+designY[0]+ " AND computer.designYear < "+designY[1];
    }
    else
    {
        filter = "computer.designYear = '"+designY[0]+"'";
    }
    return data.readComputerFromDatabase(filter);

}



