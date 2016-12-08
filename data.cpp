#include "data.h"

using namespace std;
//data layer

Data::Data()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    db.open();

    importSQL();

    readPeopleFromDatabase();
    readComputerFromDatabase();
    readConfigFromFile();
}

void Data::importSQL(){

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
                if (command.trimmed().isEmpty()) {
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

QMap<int,QMap<QString,QString>> Data::getAcceptedGender(){

    QMap<int,QMap<QString,QString>> genders;
    QSqlQuery query("SELECT id, genderName, genderChar FROM Person_Gender");
    while (query.next()) {
       int id = query.value(0).toInt();
       QString gName = query.value(1).toString();
       QString gChar = query.value(2).toString();

       QMap<QString, QString> strings{{gChar,gName}};
       genders.insert(id,strings);
    }
    return genders;
};

QSqlRelationalTableModel* Data::submitDatabaseChanges(QSqlRelationalTableModel* model){
    //model->setFilter("");
    model->submitAll();
    return model;
}

//getList returns copy of the list (vector) containing all persons in the "database"
vector<Person> Data::getPersonList()
{
    return personList;
}

//getList returns copy of the list (vector) containing all computers in the "database"
vector<Computer> Data::getComputerList()
{
    return compList;
}

//writePersonToFile writes new person to file and adds person to the main vector containing all persons(if push=1).
void Data::writePersonToDatabase(Person p, bool push)
{
    db.open();

    QSqlQuery query;
    query.prepare("INSERT INTO Person (name, genderId, birthYear, deathYear, nationality) "
                  "VALUES (:name, :gender, :birthYear, :deathYear, :nationality)");
    query.bindValue(":name", p.getName());
    query.bindValue(":gender", p.getGender());
    query.bindValue(":birthYear", p.getBirthYear());
    query.bindValue(":deathYear", p.getDeathYear());
    query.bindValue(":nationality", p.getNationality());
    query.exec();

    int ID = query.lastInsertId().toInt();
    p.setPersonID(ID);

    //add person to person list if push=1
    if(push)
    {
        personList.push_back(p);
    };
}

void Data::writeComputerToDatabase(Computer c, bool push)
{
    //TODO
    db.open();

    QSqlQuery query;
    query.prepare("INSERT INTO Computer (name, designYear, buildYear, type)"
                  "VALUES (:name, :designYear, :buildYear, :type)");
    query.bindValue(":name", c.getComputerName());
    query.bindValue(":designYear", c.getDesignYear());
    query.bindValue(":buildYear", c.getBuildYear());
    query.bindValue(":type", c.getComputerType());
    query.exec();

    int ID = query.lastInsertId().toInt();
    c.setComputerID(ID);

    //add computer to computer list if push=1
    if(push)
    {
        compList.push_back(c);
    }
    cout << "debug" << endl;
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

//readComputerFromDatabase reads current computerFile entries into main list.
//done at start up
void Data::readComputerFromDatabase()
{
    //clear list first, just in case.
    compList.clear();

    QSqlQuery query("SELECT name, designYear, buildYear, type FROM Computer");
       while (query.next())
       {
           QString name = query.value(0).toString();
           int designYear = query.value(1).toInt();
           int buildYear = query.value(2).toInt();
           QString computerType = query.value(3).toString();

           Computer newComputer(name, designYear, computerType, buildYear);
           compList.push_back(newComputer);
       }
}

//getConfig returns a copy of the config object
Config Data::getConfig()
{
    return config;
}

//writeConfigToFile takes in Config class as parameter, and writes the config settings to the config.txt file
void Data::writeConfigToFile(Config c)
{
    //todo rewrite using database/user

    /*

    //open and write in file
    ofstream file;
    file.open(configFile);

    file << "\n" << c.sortColumn << " " << c.SortOrder << " " << c.sortComputerColumn;

    //overwrites config object with new settings.
    config.sortColumn = c.sortColumn;
    config.SortOrder = c.SortOrder;
    config.sortComputerColumn = c.sortComputerColumn;

    file.close();
    */
}

//readConfigFromFile reads current config entries into main config object.
//done at start up
void Data::readConfigFromFile()
{
    //todo rewrite using database/user

    /*

    ifstream file;
    file.open(configFile);
    bool fileIsEmpty = file.peek() == ifstream::traits_type::eof(); //checks if file is empty

    string sortOrder = "";
    int sortColumn = 0;
    int sortComputerColumn = 0;

    if(!file.eof() && file.is_open() && !file.fail() && !fileIsEmpty ) //check if file, exists, is open and is generally usable
    {
        file >> sortColumn >> sortOrder >> sortComputerColumn;

        //overrwite main config object.
        config.sortColumn = sortColumn;
        config.SortOrder = sortOrder;
        config.sortComputerColumn = sortComputerColumn;

    }

    file.close();
    */
}


//removePersonFromDatabase takes person class as parameter, checks if it exists in the main person List, and removes person from both file and list.
void Data::removePersonFromDatabase(Person personToRemove)
{
    //make changes to the vector holding people
    int vectorSize = personList.size();
    for(int i=0; i < vectorSize; i++)
    {
        if(personList[i] == personToRemove)
        {
            //if found, remove person from list and file
            personList.erase(personList.begin()+i);
            rewriteDatabase();
            break;
        }
    }
}

void Data::clearDatabase()
{
    QSqlQuery query("delete from person");
}


//overwrites peopleFile with current person List.
void Data::rewriteDatabase()
{
    //first delete current peopleFile
    clearDatabase();

    int vectorSize = personList.size();
    for(int i=0; i < vectorSize; i++)
    {
        //writes person i from person list to file.
        writePersonToDatabase(personList[i],0);
    }
}

//clears both person list and peopleFile
//essentially our version of "drop table"
void Data::clearPersonInDataBase()
{
   personList.clear();
   clearDatabase();
}

//swapPersonsInDatabase overwrites originalPerson with newPerson
void Data::swapPersonsInDatabase(Person& originalP, Person& newP)
{
    //used when editing the list, so that the person you edited stays in the same
    //spot in the list instead of being added to the bottom of the list
    for(size_t i=0; i < personList.size(); i++)
    {
        if(personList[i] == originalP)
        {
            personList[i] = newP;
            rewriteDatabase();
            break;
        }
    }
}
