#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDir>

class Utils
{
public:
    Utils();
    QString capitalizeString(QString string);
    const int dummyNull = 999999;
    const QString workingDir = QDir::currentPath() + "/../";
};

#endif // UTILS_H
