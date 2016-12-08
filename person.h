#ifndef PERSON_H
#define PERSON_H

#include <time.h>
#include <cstddef>
#include <QVariant>

using namespace std;

class Person
{
public:
    //default constructor
    //requires name, gender, birthyear, deathyear, nationality
    Person(QString n, int g, int bY, int dY, QString nat);
    Person(QString n, int g, int bY, int dY, QString nat, int id);

    //set functions for editing
    void setName(QString inputName);
    void setPersonID(int ID);
    void setGender(int inputGender);
    void setBY(int inputBY);
    void setDY(int inputDY);
    void setNationality(QString inputNat);

    //returns name of Person
    QString getName() const;

    //returns only first name instants of Person
    QString getFirstName() const;

    //returns only last name instants of Person
    QString getLastName() const;

    //calculates and returns age. Calculates from death year if the person
    //is dead, but from current year if the person is still alive.
    int getAge() const;

    //returns birth year
    int getBirthYear() const;

    //returns death year
    int getDeathYear() const;

    //returns gender: F for female and M for male.
    int getGender() const;

    //returns the nationality
    QString getNationality() const;

    int getPersonId();

    //Friend functions:
    friend bool operator== (const Person lhs, const Person rhs);

private:
    int pId;
    QString name;
    int    birthYear;
    int    deathYear;
    int   gender;
    QString nationality;
};

#endif // PERSON_H
