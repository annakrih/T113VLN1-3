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

    Computer(QString cp, int by, QString cd, int dy);

    QString getComputerName() const;

    int getBuildYear () const;

    QString getComputerType() const;

    char getWasItBuilt();

    int getDesignYear();

    void setComputerID(int ID);

private:
    int cID;
    QString computerName;
    int buildYear; //0 if the computer was never built.
    QString computerType;
    int designYear;
};

#endif // COMPUTER_H
