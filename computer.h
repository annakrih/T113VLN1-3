#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <cstddef>
#include <QVariant>

using namespace std;

class Computer
{
public:
    Computer();

    Computer(string cp, int by, string cd, int dy);

    string getComputerName () const;

    int getBuildYear () const;

    string getComputerType() const;

    char getWasItBuilt();

    int getDesignYear();

    void setComputerID(QVariant ID);

private:
    QVariant cID;
    string computerName;
    int buildYear; //0 if the computer was never built.
    string computerType;
    int designYear;
};

#endif // COMPUTER_H
