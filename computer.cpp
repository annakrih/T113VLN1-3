#include "computer.h"

Computer::Computer(string cp, int by, string cd, int dy)
{
    computerName = cp;
    buildYear = by;
    computerType = cd;
    designYear = dy;
}

string Computer::getComputerName () const
{
   return computerName;
}

int Computer::getBuildYear () const
{
   return buildYear;
}

string Computer::getComputerType() const
{
   return computerType;
}

char Computer::getWasItBuilt()
{
    char wasItBuilt;

    if(buildYear == 0)
    {
        wasItBuilt = 'N';
    }
    else
    {
        wasItBuilt = 'Y';
    }
    return wasItBuilt;
}

int Computer::getDesignYear()
{
    return designYear;
}

void Computer::setComputerID(QVariant ID)
{
    cID = ID;
}


