#include "data.h"

using namespace std;
//data layer

Data::Data()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    db.open();

    importSQL();
}

void Data::importSQL()
{
    QSqlQuery query("SELECT count(name) as count FROM sqlite_master WHERE type='table'");
    query.next();
    int tables = query.value(0).toInt();

    if(!tables)
    {
        QFile schema(schemaFile);
        if (schema.open(QIODevice::ReadOnly))
        {
            QStringList schemaCommands = QTextStream(&schema).readAll().split(';');

            foreach (QString command, schemaCommands)
            {
                if (command.trimmed().isEmpty())
                {
                    continue;
                }
                if (!query.exec(command))
                {
                    qFatal(QString("One of the query failed to execute.\n Error detail: " + query.lastError().text()).toLocal8Bit());
                }
            }
            query.finish();
        }
        initializeData();
    }

}

QMap<int,QMap<QString,QString>> Data::getAcceptedGender()
{
    QMap<int,QMap<QString,QString>> genders;
    QSqlQuery query("SELECT id, genderName, genderChar FROM Person_Gender");
    while (query.next())
    {
       int id = query.value(0).toInt();
       QString gName = query.value(1).toString();
       QString gChar = query.value(2).toString();

       QMap<QString, QString> strings{{gChar,gName}};
       genders.insert(id,strings);
    }
    return genders;
}

QMap<QString, int> Data::getAcceptedComputerTypes()
{
    QMap<QString, int> computerTypes;
    QSqlQuery query("SELECT id, typeName FROM Computer_Type");
    while(query.next())
    {
        int id = query.value(0).toInt();
        QString typeName = query.value(1).toString();

        computerTypes.insert(typeName, id);
    }

    return computerTypes;
}

QSqlRelationalTableModel* Data::submitDatabaseChanges(QSqlRelationalTableModel* model)
{
    model->submitAll();
    return model;
}

//readPeopleFromDatabase reads current peopleFile entries into main list.
//done at start up
QSqlRelationalTableModel * Data::readPeopleFromDatabase(QString filter)
{
   QSqlRelationalTableModel  *model = new QSqlRelationalTableModel (0, db);
   model->setTable("person");
   model->setRelation(2, QSqlRelation("Person_Gender", "id", "GenderName"));

   model->setFilter(filter);

   model->select();
   model->setEditStrategy(QSqlTableModel::OnManualSubmit);

   return model;
}

QSqlRelationalTableModel * Data::readComputerFromDatabase(QString filter)
{
   QSqlRelationalTableModel  *model = new QSqlRelationalTableModel (0, db);
   model->setTable("computer");
   model->setRelation(2, QSqlRelation("Computer_Type", "id", "typeName"));
   model->setFilter(filter);

   model->select();
   model->setEditStrategy(QSqlTableModel::OnManualSubmit);

   return model;
}

QSqlQueryModel* Data::readComputerRelation(QString filter){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT P.* from Person as P INNER JOIN person_computer as PC on p.id = PC.personId INNER JOIN computer as C on PC.computerId = C.id where C.id ="+filter);

    return model;
};

QSqlQueryModel* Data::readPersonRelation(QString filter){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT C.* from Computer as C INNER JOIN person_computer as PC on C.id = PC.computerId INNER JOIN person as p on PC.personId = P.id where P.id = "+filter);

    return model;
};


void Data::clearDatabase()
{
    QSqlQuery query("delete from person");
}

void Data::initializeData()
{
    initializePersons();
    initializeComputers();
    initializeRelations();
}

void Data::initializePersons()
{
    QSqlQuery query;
    query.prepare("INSERT INTO person (name, genderId, nationality, birthYear, deathYear)"
                      "VALUES (:name, :genderId, :nationality, :birthYear, :deathYear)");

    QFile file(initialPersons);
    if(! file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qFatal(QString("Failed to open file to initialize persons."+query.lastError().text() ).toLocal8Bit() );
        return;
    }

    QStringList inputList = QTextStream(&file).readAll().split(',');

    for (int i=0; i < inputList.size(); i += 5)
    {
        QString name = inputList[i];
        query.bindValue(":name", name.trimmed());
        int gender = inputList[i+1] == "M" ? 1 : 0;
        query.bindValue(":genderId", gender);
        query.bindValue(":nationality", inputList[i+4]);
        query.bindValue(":birthYear", inputList[i+2]);
        query.bindValue(":deathYear", inputList[i+3]);

        if (!query.exec())
        {
            qFatal(QString("One of the query failed to execute.\n Error detail: " + query.lastError().text()).toLocal8Bit());
        }
    }
    file.close();
    query.finish();
}

void Data::initializeComputers()
{
    QSqlQuery query;
    query.prepare("INSERT INTO computer (name, designYear, buildYear, typeId)"
                      "VALUES (:name, :designYear, :buildYear, :typeId)");

    QFile file(initialComputers);
    if(! file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qFatal(QString("Failed to open file to computers."+query.lastError().text() ).toLocal8Bit());
        return;
    }

    QStringList inputList = QTextStream(&file).readAll().split(',');

    for (int i=0; i < inputList.size(); i += 4)
    {
        QString name = inputList[i];
        query.bindValue(":name", name.trimmed());
        query.bindValue(":typeId", inputList[i+1]);
        query.bindValue(":designYear", inputList[i+2]);
        query.bindValue(":buildYear", inputList[i+3]);

        if (!query.exec())
        {
            qFatal(QString("One of the query failed to execute.\n Error detail: " + query.lastError().text()).toLocal8Bit());
        }
    }
    file.close();
    query.finish();
}

void Data::initializeRelations()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Person_Computer (personId, computerId)"
                      "VALUES (:personId, :computerId)");

    QFile file(initialRelations);
    if(! file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qFatal(QString("Failed to open file to initialize relations."+query.lastError().text() ).toLocal8Bit());
        return;
    }

    QStringList inputList = QTextStream(&file).readAll().split(',');


    for (int i=0; i < (inputList.size()-1); i += 2)
    {
        query.bindValue(":personId", inputList[i]);
        query.bindValue(":computerId", inputList[i+1]);

        if (!query.exec())
        {
            qFatal(QString("One of the query failed to execute.\n Error detail: " + query.lastError().text()).toLocal8Bit());
        }
    }
    file.close();
    query.finish();
}
