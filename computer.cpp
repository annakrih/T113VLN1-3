#include "computer.h"

Computer::Computer(QString cp, int by, QString cd, int dy)
{
    computerName = cp;
    buildYear = by;
    computerType = cd;
    designYear = dy;
}

QString Computer::getComputerName () const
{
   return computerName;
}

int Computer::getBuildYear () const
{
   return buildYear;
}

QString Computer::getComputerType() const
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

void Computer::setComputerID(int ID)
{
    cID = ID;
}


