#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

using namespace std;

class Computer
{
public:
    Computer();

    Computer(string cp, int by, string cd);

    string getcomputerName () const;

    int getBuildYear () const;

    string getComputerName() const;

    bool wasItBuilt();

private:
    string computerName;
    int buildYear;
    string computerDesign;

};

#endif // COMPUTER_H
