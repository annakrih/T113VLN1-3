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

string Computer::getComputerName() const
{
   return computerDesign;
}

bool Computer::wasItBuilt()
{
    //TODO
}


