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

QSqlQueryModel * Domain::getPersonRelationModel(QString filter)
{
    return data.readPersonRelation(filter);
}

QSqlRelationalTableModel * Domain::getComputerModel(QString filter)
{
    return data.readComputerFromDatabase(filter);
}

QSqlQueryModel * Domain::getComputerRelationModel(QString filter)
{
    return data.readComputerRelation(filter);
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

QSqlRelationalTableModel * Domain::searchPersonName(QString name)
{
    QString filter = "person.name like '%"+name+"%'";
    return data.readPeopleFromDatabase(filter);
}

QSqlRelationalTableModel * Domain::searchPersonGender(QString search)
{
    QString intSearch = 0;
    if(search == "Male" || search == "male" || search == "m" || search == "M")
    {
        intSearch = "1";
    }
    if(search == "Female" || search == "female" || search == "f" || search == "M")
    {
        intSearch = "2";
    }

    QString filter = "person.genderId like '%"+intSearch+"%'";
    return data.readPeopleFromDatabase(filter);
}

QSqlRelationalTableModel * Domain::searchPersonNationality(QString search)
{
    QString filter = "person.nationality like '%"+search+"%'";
    return data.readPeopleFromDatabase(filter);
}

QSqlRelationalTableModel * Domain::searchPersonBY(QString search)
{
    QStringList birthY = search.split(" ");

    QString filter;
    if(birthY.size() == 2)
    {
        filter = "person.birthYear > "+birthY[0]+ " AND person.birthYear < "+birthY[1];
    }
    else
    {
        filter = "person.birthYear = '"+birthY[0]+"'";
    }
    return data.readPeopleFromDatabase(filter);

}

QSqlRelationalTableModel * Domain::searchPersonDY(QString search)
{
    QStringList deathY = search.split(" ");

    QString filter;
    if(deathY.size() == 2)
    {
        filter = "person.deathYear > "+deathY[0]+ " AND person.deathYear < "+deathY[1];
    }
    else
    {
        filter = "person.deathYear = '"+deathY[0]+"'";
    }
    return data.readPeopleFromDatabase(filter);

}

QSqlRelationalTableModel * Domain::searchComputerName(QString name)
{
    QString filter = "computer.name like '%"+name+"%'";
    return data.readComputerFromDatabase(filter);
}

QSqlRelationalTableModel * Domain::searchComputerType(QString search)
{
    QMap<QString, int> types = data.getAcceptedComputerTypes();

    QVariant typeId = types.value(utils.capitalizeString(search));

    QString filter = "computer.typeId = '"+typeId.toString()+"'";
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

QSqlRelationalTableModel * Domain::searchComputerBY(QString search)
{
    QStringList buildY = search.split(" ");

    QString filter;
    if(buildY.size() == 2)
    {
        filter = "computer.buildYear > "+buildY[0]+ " AND computer.buildYear < "+buildY[1];
    }
    else
    {
        filter = "computer.buildYear = '"+buildY[0]+"'";
    }
    return data.readComputerFromDatabase(filter);
}

void Domain::createPCRelation(int p, int c){
    data.createPCRelation(p,c);
}

