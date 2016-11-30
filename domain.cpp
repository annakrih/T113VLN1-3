#include "domain.h"
#include "data.h"
#include <algorithm>
#include <string>
#include <fstream>

#include <iostream>
using namespace std;

//domain layer

struct PersonComparison {
  bool operator() (Person i,Person j) { return (i.getName()<j.getName());}
};

Domain::Domain()
{

}

void Domain::addPerson(Person p){
    data.writePersonToFile(p);
}

vector<Person> Domain::getPersonList(/* TODO: parameters */)
{
    vector<Person> people = data.getList();

    //Person p("Duran Duran");
    //Person p2("Madonna");
    //Person p3("David Bowie");

    //people.push_back(p);
    //people.push_back(p2);
    //people.push_back(p3);

    // TODO: business logic!

    // Sort by name:
    //PersonComparison cmp;
    //std::sort(people.begin(), people.end(), cmp);

    return people;
}

vector<Person> Domain::searchPersonName(string search){
    vector<Person> searchList, people = data.getList();

    for(size_t i= 0; i < people.size(); i++ ){
        string name = people[i].getName();
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        transform(search.begin(), search.end(), search.begin(), ::tolower);


        if(search.find(' ') != string::npos){
            search.erase(search.begin());
        }

        if(name.find(search) != string::npos){
            searchList.push_back(people[i]);
        }
    }
    return searchList;
}

vector<Person> Domain::searchPersonNationality(string search){
    vector<Person> searchList, people = data.getList();

    for(size_t i= 0; i < people.size(); i++ ){
        string nationality = people[i].getNationality();
        transform(nationality.begin(), nationality.end(), nationality.begin(), ::tolower);
        transform(search.begin(), search.end(), search.begin(), ::tolower);

        if(nationality.find(search) != string::npos){
            searchList.push_back(people[i]);
        }
    }
    return searchList;
}

vector<Person> Domain::searchPersonGender(char search){
    vector<Person> searchList, people = data.getList();

    for(size_t i= 0; i < people.size(); i++ ){
        char gender = people[i].getGender();
        gender = (tolower(gender));
        search = (tolower(search));
        if(search == gender){
            searchList.push_back(people[i]);
        }
    }
    return searchList;
}

vector<Person> Domain::searchPersonBirth(int from, int to){
    vector<Person> searchList, people = data.getList();

    if(to == 9999){
        to = from;
    }

    for(size_t i= 0; i < people.size(); i++ ){
        int birthYear = people[i].getBirthYear();

        if(birthYear >= from && birthYear <= to){
            searchList.push_back(people[i]);
        }
    }
    return searchList;
}

vector<Person> Domain::searchPersonDeath(int from, int to){
    vector<Person> searchList, people = data.getList();

    if(to == 9999){
        to = from;
    }

    for(size_t i= 0; i < people.size(); i++ ){
        int deathYear = people[i].getDeathYear();

        if(deathYear >= from && deathYear <= to && deathYear != 0){
            searchList.push_back(people[i]);
        }
    }

    return searchList;
}



