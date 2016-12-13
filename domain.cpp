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

QSqlQueryModel * Domain::getDeletePersonTable()
{
    return data.deleteAllPersons();
}

QSqlQueryModel * Domain::getDeleteComputerTable()
{
    return data.deleteAllComputers();
}

QSqlQueryModel * Domain::getDeleteRelationTable()
{
    return data.deleteAllRelations();
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


void Domain::createPCRelation(int p, int c){
    data.createPCRelation(p,c);
}

QSqlRelationalTableModel * Domain::searchPerson(QString searchInput)
{
    return searchPerson(searchInput, 0, "", "", "", "", "");
}


QSqlRelationalTableModel * Domain::searchPerson(QString searchInput, QString gender, QString BYfrom, QString BYto, QString DYfrom, QString DYto, QString nationality)
{
    QString filter = "";
    bool firstFilter = true;

    //name filter
    if( !(searchInput==""))
    {
        filter += "person.name like '%"+searchInput+"%'";
        firstFilter = false;
    }

    //gender filter
    if( !(gender=="" || gender =="0"))
    {
        if(!firstFilter)
        {
            filter += " AND ";
        }

        filter += "person.genderId like '%"+gender+"%'";
        firstFilter = false;
    }

    //birthYear filter
    if( !(BYfrom == "") || !(BYto=="") )
    {
        if(!firstFilter)
        {
            filter += " AND ";
        }

        if(!(BYfrom == "") && !(BYto==""))
        {
            filter += "person.birthYear > "+BYfrom+ " AND person.birthYear < "+BYto;
        }
        else if(!(BYfrom == ""))
        {
            filter += "person.birthYear > '"+BYfrom+"'";
        }
        else if(!(BYto == ""))
        {
            filter += "person.birthYear < '"+BYto+"'";
        }
        firstFilter = false;
    }

    //DeathYear filter
    if( !(DYfrom == "") || !(DYto=="") )
    {
        if(!firstFilter)
        {
            filter += " AND ";
        }

        if(!(DYfrom == "") && !(DYto==""))
        {
            filter += "person.deathYear > "+DYfrom+ " AND person.deathYear < "+DYto;
        }
        else if(!(DYfrom == ""))
        {
            filter += "person.deathYear > '"+DYfrom+"'";
        }
        else if(!(DYto == ""))
        {
            filter += "person.deathYear < '"+DYto+"'";
        }
        firstFilter = false;
    }

    //gender filter
    if( !(nationality=="0"))
    {
        if(!firstFilter)
        {
            filter += " AND ";
        }

        filter += "person.nationalityId like '%"+nationality+"%'";
        firstFilter = false;
    }
    return data.readPeopleFromDatabase(filter);
}

QSqlRelationalTableModel * Domain::searchComputer(QString searchNameInput)
{
    return searchComputer(searchNameInput, "", "", "", "", "");
}

QSqlRelationalTableModel * Domain::searchComputer(QString searchNameInput, QString DYfrom, QString DYto, QString BYfrom, QString BYto, QString type)
{
    QString filter = "";
    bool firstFilter = true;

    //name filter
    if( !(searchNameInput==""))
    {
        filter += "computer.name like '%"+searchNameInput+"%'";
        firstFilter = false;
    }

    //DesignYear filter
    if( !(DYfrom == "") || !(DYto=="") )
    {
        if(!firstFilter)
        {
            filter += " AND ";
        }

        if(!(DYfrom == "") && !(DYto==""))
        {
            filter += "computer.designYear >= "+DYfrom+ " AND computer.designYear <= "+DYto;
        }
        else if(!(DYfrom == ""))
        {
            filter += "computer.designYear >= '"+DYfrom+"'";
        }
        else if(!(DYto == ""))
        {
            filter += "computer.designYear <= '"+DYto+"'";
        }
        firstFilter = false;
    }

    //BuildYear filter
    if( !(BYfrom == "") || !(BYto=="") )
    {
        if(!firstFilter)
        {
            filter += " AND ";
        }

        if(!(BYfrom == "") && !(BYto==""))
        {
            filter += "computer.buildYear >= "+BYfrom+ " AND computer.buildYear <= "+BYto;
        }
        else if(!(BYfrom == ""))
        {
            filter += "computer.buildYear >= '"+BYfrom+"'";
        }
        else if(!(BYto == ""))
        {
            filter += "computer.buildYear <= '"+BYto+"'";
        }
        firstFilter = false;
    }


    //ComputerType filter
    if( !(type=="0" || type==""))
    {
        if(!firstFilter)
        {
            filter += " AND ";
        }

        filter += "computer.typeId like '%"+type+"%'";
    }

    std::cout << endl << filter.toStdString() << endl;
    return data.readPeopleFromDatabase(filter);
}

QString Domain::getCssString()
{
    return data.importCss();
}
