#include "computer.h"

Computer::Computer(string cp, int by, string cd, char wib, int dy)
{
    computerName = cp;
    buildYear = by;
    computerType = cd;
    wasItBuilt = wib;
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
    return wasItBuilt;
}


