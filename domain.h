#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include "person.h"
#include "data.h"
#include "config.h"

using namespace std;

//domain layer
class Domain
{
private:
    //declare data variable, to have access to lower layer.
    Data data;
    static const int dummyNull = 9999;
public:
    Domain();

    //Gets the vector that holds the Persons
    vector<Person> getPersonList();

    //Gets the vector that holds the Computers
    vector<Computer> getCList();

    //Function that uses data.removePersonFromDatabase and deletes personToRemove from vector and database
    //passes a person class to the data layer for processing
    void removePerson(Person personToRemove);

    //Function that uses data.editPersonInDatabase to edit a Person.
    //passes a person class to the data layer for processing
    void editPerson(Person personToEdit);

    //Function that uses data.clearPersonInDatabase to clear everything in the list.
    void clearPerson();

    //Calls the function data.swapPersonsInDatabase to swap originalP with newP
    void swapPerson(Person& originalP, Person& newP);

    //Search functions based on what you want to search by:
    //they take in a vector of person to search in, and a search parameter.
    vector<Person> searchPersonName(vector<Person> people, string search);           //name
    vector<Person> searchPersonNationality(vector<Person> people, string search);    //nationality
    vector<Person> searchPersonGender(vector<Person> people, char search);           //gender
    vector<Person> searchPersonBirth(vector<Person> people, int from, int to = dummyNull);//birth year
    vector<Person> searchPersonDeath(vector<Person> people, int from, int to = dummyNull);//death year
    vector<Person> searchPersonAge (vector<Person> people, int from, int to = dummyNull); //age

    //Search functions based on what you want to search by:
    //they take in a vector of computer to search in, and a search parameter.
    vector<Computer> searchComputerName(vector<Computer> comp, string search); //name
    vector<Computer> searchCDName(vector<Computer> comp, string search); //computerdesign
    vector<Computer> searchCBuildYear(vector<Computer> comp, int from, int to); //buildyear


    //Sort functions based on what you want to sort by:
    //they take in a vector of person to sort, and a sort order ("desc or "asc).
    vector<Person> sortPersonByName(string sortOrder,   vector<Person> pList);      // name
    vector<Person> sortPersonByGender(string sortOrder, vector<Person> pList);      // gender
    vector<Person> sortPersonByBY(string sortOrder, vector<Person> pList);          // birth year
    vector<Person> sortPersonByDY(string sortOrder, vector<Person> pList);          // death year
    vector<Person> sortPersonByNat(string sortOrder,    vector<Person> pList);      // nationality
    vector<Person> sortPersonByAge(string sortOrder,    vector<Person> pList);      // age
    vector<Person> sortPersonByDefault(vector<Person> pList);                       // based on config settings

    //gets config from data layer
    Config getConfig();

    //passes on a Confic object to overrwrite the current config
    void setConfig(Config c);

    //Function used for adding a person to the list vector
    void addPerson(Person p);
};

#endif // Domain_H
