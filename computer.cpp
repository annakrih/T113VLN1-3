#include "computer.h"
#include <cstddef>


Computer::Computer(string cp, int by, string cd)
{
    computerName = cp;
    buildYear = by;
    computerDesign = cd;
}

string Computer::getcomputerName () const
{
   return computerName;
}

int Computer::getBuildYear () const
{
   return buildYear;
}

string Computer::getComputerType() const
{
   return computerDesign;
}

bool Computer::wasItBuilt()
{
    if(buildYear == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


