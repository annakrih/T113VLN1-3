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

   //todo use filter as search
   /*
   QString test = "An";
   QString filter = "person.name like '%"+test+"%' ";
   model->setFilter(filter);

   //sort example
   model->setSort(1, Qt::SortOrder::DescendingOrder);
   */

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
    model->setQuery("SELECT P.* from Person as P left join person_computer as PC on p.id = PC.personId left join computer as C on PC.computerId = C.id where C.id ="+filter);

    return model;
};

QSqlQueryModel* Data::readPersonRelation(QString filter){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT C.* from Computer as C left join person_computer as PC on C.id = PC.computerId left join person as p on PC.personId = P.id where P.id = "+filter);

    return model;
};


void Data::clearDatabase()
{
    QSqlQuery query("delete from person");
}

void Data::initializeData()
{
    QSqlQuery query;
    query.next();
  //  int tables = query.value(0).toInt();

   // if(!tables)
    {
        QFile file("database/personsInitialData.csv");
        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QStringList fileCommands = QTextStream(&file).readAll().split(',');

            foreach (QString command, fileCommands)
            {
                //query("SELECT count(name) as count FROM sqlite_master WHERE type='table'");
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
    }
}
