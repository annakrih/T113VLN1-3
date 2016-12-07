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
    readConfigFromFile();
}

void Data::importSQL(){

    QSqlQuery query("SELECT count(name) as count FROM sqlite_master WHERE type='table'");
    query.next();
    int tables = query.value(0).toInt();

    if(!tables)
    {
        QFile schema(path+"/database/schema.sql");
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
                query.finish();
            }
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
    query.bindValue(":name", QString::fromStdString(p.getName()));
    query.bindValue(":gender", p.getGender());
    query.bindValue(":birthYear", p.getBirthYear());
    query.bindValue(":deathYear", p.getDeathYear());
    query.bindValue(":nationality", QString::fromStdString(p.getNationality()));
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
}

//readPeopleFromDatabase reads current peopleFile entries into main list.
//done at start up
void Data::readPeopleFromDatabase()
{
    //clear list first, just in case.
    personList.clear();

    QSqlQuery query("SELECT id,name, genderId, birthYear, deathYear, nationality FROM Person");
       while (query.next()) {
           int id = query.value(0).toInt();
           string name = QString(query.value(1).toString()).toStdString();
           int gender = query.value(2).toInt();
           int birthYear = query.value(3).toInt();
           int deathYear = query.value(4).toInt();
           string nationality = QString(query.value(5).toString()).toStdString();

           Person newPerson(name, gender, birthYear, deathYear, nationality,id);
           personList.push_back(newPerson);
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
    //open and write in file
    ofstream file;
    file.open(configFile);

    file << "\n" << c.sortColumn << " " << c.SortOrder;

    //overwrites config object with new settings.
    config.sortColumn = c.sortColumn;
    config.SortOrder = c.SortOrder;

    file.close();
}

//readConfigFromFile reads current config entries into main config object.
//done at start up
void Data::readConfigFromFile()
{

    ifstream file;
    file.open(configFile);
    bool fileIsEmpty = file.peek() == ifstream::traits_type::eof(); //checks if file is empty

    string sortOrder = "";
    int sortColumn = 0;

    if(!file.eof() && file.is_open() && !file.fail() && !fileIsEmpty ) //check if file, exists, is open and is generally usable
    {
        file >> sortColumn >> sortOrder;

        //overrwite main config object.
        config.sortColumn = sortColumn;
        config.SortOrder = sortOrder;

    }

    file.close();
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

void Data::clearDatabase(){
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
