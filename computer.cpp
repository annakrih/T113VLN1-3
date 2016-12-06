#include "computer.h"
#include <cstddef>


Computer::Computer(string cp, int by, string ct, char wib, int dy)
{
    computerName = cp;
    buildYear = by;
    computerType = ct;
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

int Computer::desigYear()
{
    return designYear;
}


