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
<<<<<<< HEAD
    int buildYear;
    string computerType;
    char wasItBuilt;
    int designYear;

=======
    int buildYear; //0 if the computer was never built.
    string computerDesign;
>>>>>>> origin/master
};

#endif // COMPUTER_H
