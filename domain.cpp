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

QSqlRelationalTableModel * Domain::getComputerModel(QString filter)
{
    return data.readComputerFromDatabase(filter);
}


QSqlRelationalTableModel * Domain::getPCRelationModel()
{
    return data.readPCRelationFromDatabase();
}


QSqlRelationalTableModel * Domain::deletePersonTable()
{
    return data.deleteAllPersons();
}

QSqlRelationalTableModel * Domain::deleteComputerTable()
{
    return data.deleteAllComputers();
}

QSqlRelationalTableModel *Domain::deleteRelationTable()
{
    return data.deleteAllRelations();
}

int Domain::getNextAutoId(QString table)
{
    return data.getNextAutoId(table);
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

QMap<QString, int> Domain::getAcceptedComputerTypeName()
{
    return data.getAcceptedComputerTypes();
}

QMap<QString, int> Domain::getAcceptedNationality()
{
    return data.getAcceptedNationality();
}

QString Domain::getCssString()
{
    return data.importCss();
}

void Domain::initializeData()
{
    data.initializeData();
}
