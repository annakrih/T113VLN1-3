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

    QSqlQuery query(db);
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
    query.prepare("INSERT INTO Person (name, gender, birthYear, deathYear, nationality) "
                  "VALUES (:name, :gender, :birthYear, :deathYear, :nationality)");
    query.bindValue(":name", QString::fromStdString(p.getName()));
    query.bindValue(":gender", QString::fromStdString(string(1,p.getGender())));
    query.bindValue(":birthYear", p.getBirthYear());
    query.bindValue(":deathYear", p.getDeathYear());
    query.bindValue(":nationality", QString::fromStdString(p.getNationality()));
    query.exec();

    QVariant ID = query.lastInsertId();
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

    QSqlQuery query("SELECT name, gender, birthYear, deathYear, nationality FROM Person");
       while (query.next()) {
           QString nameQ = query.value(0).toString();
           QString genderQ = query.value(1).toString();
           qint32 birthYearQ = query.value(2).toInt();
           qint32 deathYearQ = query.value(3).toInt();
           QString nationalityQ = query.value(4).toString();

           string name = nameQ.toStdString();
           string nationality = nationalityQ.toStdString();
           string strGender = genderQ.toStdString();
           const char* gender = strGender.c_str();
           int birthYear = birthYearQ;
           int deathYear = deathYearQ;

           Person newPerson(name, *gender, birthYear, deathYear, nationality);
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
