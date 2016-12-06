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

    Computer(string cp, int by, string cd);

    string getComputerName () const;

    int getBuildYear () const;

    string getComputerType() const;

    bool wasItBuilt();

private:
    QVariant cID;
    string computerName;
    int buildYear; //0 if the computer was never built.
    string computerDesign;
};

#endif // COMPUTER_H
