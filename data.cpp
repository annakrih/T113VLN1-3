#include "data.h"

using namespace std;
//data layer

Data::Data()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    db.open();

    importSchema();
}

void Data::importSchema()
{
    QSqlQuery query("SELECT count(name) as count FROM sqlite_master WHERE type='table'");
    query.next();
    int tables = query.value(0).toInt();

    if(!tables)
    {
        qWarning(QString("No database found, creating tables and importing data").toLocal8Bit());
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

QMap<QString, int> Data::getAcceptedNationality()
{
    QMap<QString, int> nationality;
    QSqlQuery query("SELECT id, countryName FROM person_nationality");
    while(query.next())
    {
        int id = query.value(0).toInt();
        QString countryName = query.value(1).toString();

        nationality.insert(countryName, id);
    }

    return nationality;
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
   model->setRelation(2, QSqlRelation("Person_Gender", "id", "genderName"));
   model->setRelation(3, QSqlRelation("Person_Nationality", "id", "countryName"));

   model->setHeaderData(1, Qt::Horizontal, "Name");
   model->setHeaderData(2, Qt::Horizontal, "Gender");
   model->setHeaderData(3, Qt::Horizontal, "Nationality");
   model->setHeaderData(4, Qt::Horizontal, "Birth Year");
   model->setHeaderData(5, Qt::Horizontal, "Death Year");


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

   model->setHeaderData(1, Qt::Horizontal, "Name");
   model->setHeaderData(2, Qt::Horizontal, "Type");
   model->setHeaderData(3, Qt::Horizontal, "Design Year");
   model->setHeaderData(4, Qt::Horizontal, "Build Year");

   model->select();
   model->setEditStrategy(QSqlTableModel::OnManualSubmit);

   return model;
}

QSqlQueryModel* Data::readComputerRelation(QString id)
{

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT P.* from Person as P INNER JOIN person_computer as PC on p.id = PC.personId INNER JOIN computer as C on PC.computerId = C.id where C.id ="+id);

    return model;
}

QSqlQueryModel* Data::readPersonRelation(QString id)
{

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT C.* from Computer as C INNER JOIN person_computer as PC on C.id = PC.computerId INNER JOIN person as p on PC.personId = P.id where P.id = "+id);

    return model;
}

QSqlQueryModel* Data::deleteAllPersons()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("DELETE FROM Person");
    model->setQuery("DELETE FROM sqlite_sequence WHERE name=Person");

    model->setQuery("DELETE FROM Person_Computer");
    model->setQuery("DELETE FROM sqlite_sequence WHERE name=Person_Computer");

    return model;
}

QSqlQueryModel* Data::deleteAllComputers()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("DELETE FROM Computer");
    model->setQuery("DELETE FROM sqlite_sequence WHERE name=Computer");

    model->setQuery("DELETE FROM Person_Computer");
    model->setQuery("DELETE FROM sqlite_sequence WHERE name=Person_Computer");

    return model;
}

QSqlQueryModel* Data::deleteAllRelations()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    model->setQuery("DELETE FROM Person_Computer");
    model->setQuery("DELETE FROM sqlite_sequence WHERE name=Person_Computer");

    return model;
}


void Data::initializeData()
{
    QFile gender(initialGender);
    QFile nationality(initialNationality);
    QFile person(initialPerson);
    QFile computeryType(initialComputerType);
    QFile computer(initialComputer);
    QFile personComputer(initialPerson_Computer);
    importCSV("Person_Gender", gender);
    importCSV("Person_Nationality", nationality);
    importCSV("Person", person);
    importCSV("computer_type", computeryType);
    importCSV("computer", computer);
    importCSV("person_computer", personComputer);
}

void Data::createPCRelation(int p, int c)
{

    QSqlQuery query;
    query.prepare("INSERT INTO Person_Computer (personId, computerId)"
                      "VALUES (:personId, :computerId)");

    query.bindValue(":personId", p);
    query.bindValue(":computerId", c);


    if (!query.exec())
    {
        qFatal(QString("One of the query failed to execute.\n Error detail: " + query.lastError().text()).toLocal8Bit());
    }

    query.finish();

}

//todo deal with commas in values
void Data::importCSV(QString tableName, QFile & csvFile)
{
    if(!csvFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning(QString("Failed to open file:"+csvFile.fileName()+".").toLocal8Bit() );
        return;
    }

    QStringList fileRow = QTextStream(&csvFile).readAll().split('\n');
    QStringList tableColumn = QTextStream(&fileRow[0]) .readAll().split(',');

    QString queryColumns, queryValues, queryString;
    foreach(QString column, tableColumn)
    {
        column = column.trimmed();
        queryColumns.append(column+",");
        queryValues.append(":"+column+",");
    }
    queryColumns.chop(1);
    queryValues.chop(1);
    fileRow.pop_front();

    queryString = "INSERT INTO "+tableName+"("+queryColumns+") Values ("+queryValues+")";


    QSqlQuery query;
    query.prepare(queryString);

    foreach (QString row, fileRow)
    {

        QStringList columns = QTextStream(&row).readAll().split(QRegularExpression(","));
        for(int i = 0; i < columns.size(); i++)
        {
            std:cout << QString(":"+tableColumn[i].trimmed()+","+ columns[i].trimmed()+"\n").toStdString();
            query.bindValue(":"+tableColumn[i].trimmed(), columns[i].trimmed());
        }

        if (!query.exec())
        {
            qFatal(QString("One of the query failed to execute.\n Error detail: " + query.lastError().text()).toLocal8Bit());
        }
    }
    csvFile.close();
    query.finish();
}

//read css file
QString Data::importCss()
{
    //fall sem sækir css skrá
    QFile file(utils.workingDir+"stylefile.css");
    file.open(QFile::ReadOnly);
    QString StyleFile = QTextStream(&file).readAll();

    return StyleFile;
}
