#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

using namespace std;

class Computer
{
public:
    Computer();

    Computer(string cp, int by, string ct, char wib, int dy);

    string getComputerName () const;

    int getBuildYear () const;

    string getComputerType() const;

    char getWasItBuilt();

    int desigYear();

private:
    string computerName;
    int buildYear;
    string computerType;
    char wasItBuilt;
    int designYear;

};

#endif // COMPUTER_H
