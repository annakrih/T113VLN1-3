#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDir>
#include <QDate>

class Utils
{
public:
    Utils();
    QString capitalizeString(QString string);
    const int dummyNull = 999999;
    const QString workingDir = QDir::currentPath() + "/../";
    const int getYear = QDate::currentDate().year();
};

#endif // UTILS_H
