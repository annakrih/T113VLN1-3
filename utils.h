#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDir>
#include <QDate>
#include <QStringList>

class Utils
{
public:
    //default constructor
    Utils();

    //function used to capitalize first character of every word in a string
    QString capitalizeString(QString string);

    //string to get current working directory
    const QString workingDir = QDir::currentPath() + "/../";

    //gets current year
    const int getYear = QDate::currentDate().year();
};

#endif // UTILS_H
