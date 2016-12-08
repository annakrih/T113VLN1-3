#ifndef CONFIG_H
#define CONFIG_H

#include <QString>


using namespace std;

//poco class that holds config settings;
class Config
{
public:
    Config(); //default constructor
    Config(QString sO, int sC, int sCC); //constructor with 2 parameters usage example ("asc",1)
    QString SortOrder;       //sort order, either "asc" or "desc"
    int sortColumn;         //sortColumn corresponds to the column position in the list from left to right.
    int sortComputerColumn; //sortComputerColumn corresponds to the column position in the list from left to right.
};

#endif // CONFIG_H
