#include "person.h"
#include "utils.h"

//default constructor
//requires name, gender, birthyear, deathyear, nationality
Person::Person(QString n, int g, int bY, int dY, QString nat)
{
    name = n;
    gender = g;
    birthYear = bY;
    deathYear = dY;
    nationality = nat;
}

Person::Person(QString n, int g, int bY, int dY, QString nat, int id)
{
    pId = id;
    name = n;
    gender = g;
    birthYear = bY;
    deathYear = dY;
    nationality = nat;
}

QString Person::getName() const
{
    return name;
}

QString Person::getFirstName() const
{
    return name.leftRef(name.indexOf(" ")).toString();
}

QString Person::getLastName() const
{
    return name.leftRef(name.lastIndexOf(" ")).toString();
}

int Person::getAge() const
{
    if(deathYear == 0)
    {
        time_t t = time(NULL);
        tm* timePtr = localtime(&t);
        int currentYear = timePtr->tm_year + 1900;
        return currentYear - birthYear;
    }
    return deathYear - birthYear;
}

int Person::getBirthYear() const
{
    return birthYear;
}

int Person::getDeathYear() const
{
    return deathYear;
}

int Person::getGender() const
{
    return gender;
}

QString Person::getNationality() const
{
    return nationality;
}

int Person::getPersonId()
{
    return pId;
}

void Person::setName(QString inputName)
{
    name = inputName;
}

void Person::setPersonID(int ID)
{
    pId = ID;
}

void Person::setGender(int inputGender)
{
    gender = inputGender;
}

void Person::setBY(int inputBY)
{
    birthYear = inputBY;
}

void Person::setDY(int inputDY)
{
    deathYear = inputDY;
}

void Person::setNationality(QString inputNat)
{
    nationality = inputNat;
}

bool operator== (const Person lhs, const Person rhs) //override == operator, so we can compare 2 person variables
{
    bool result=1;

    if( !(lhs.name == rhs.name) )
    {
        result = 0;
    }

    if( !(lhs.birthYear == rhs.birthYear) )
    {
        result = 0;
    }

    if( !(lhs.deathYear == rhs.deathYear) )
    {
        result = 0;
    }
    if( !(lhs.gender == rhs.gender) )
    {
        result = 0;
    }

    if( !(lhs.nationality == rhs.nationality) )
    {
        result = 0;
    }

    return result;
}
