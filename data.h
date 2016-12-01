#ifndef DATA_H
#define DATA_H
#include <vector>
#include "person.h"

using namespace std;

//data layer

class Data
{
private:
    //vector contains the list
    vector<Person> list;
public:
    Data();

    vector<Person> getList();
    void writePersonToFile(Person P);
    void updateSort(vector<Person> pList);
    void readPeopleFromFile();

    void removePersonFromDatabase(Person personToRemove);
        //removes personToRemove from the vector and database.

    void rewriteDatafile();
        //overwrites data in people.txt

    void writeSinglePersonToOpenFile(Person p, ofstream& out);
<<<<<<< HEAD
        //writes person p in file. Opens the file before and use ostream
=======
        //writes person p in file via the out stream variable.
>>>>>>> origin/master

    void editPersonInDatabase(Person personToEdit);
        //Edits personToEdit in vector and database
    void clearPersonInDataBase();

};

#endif // DATA_H
