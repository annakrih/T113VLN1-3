#include "customproxymodel.h"

#include <iostream>

CustomProxyModel::CustomProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

void CustomProxyModel::setFilterKeyColumns(const QList<int> &filterColumns)
{
    columnPatterns.clear();

    foreach(int column, filterColumns)
        columnPatterns.insert(column, QString());
}

void CustomProxyModel::addFilterFixedString(int column, const QString &pattern)
{
    if(!columnPatterns.contains(column))
        return;

    columnPatterns[column] = pattern;
}

void CustomProxyModel::setRelationColumn(QList<int> list)
{
    relationColumn = list;
}

bool CustomProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if(columnPatterns.isEmpty())
    {
        return true;
    }

    bool ret = false;

    QMapIterator<int, QString> i(columnPatterns);

    while (i.hasNext())
    {
        i.next();
        QModelIndex index = sourceModel()->index(sourceRow, i.key(), sourceParent);
        if(relationColumn.contains(i.key()))
        {
            ret = (index.data().toString().toLower() == (i.value().toLower()));
        }
        else
        {
        if(relationColumn.contains(i.key()))
        {
            ret = (index.data().toString().toLower() == (i.value().toLower())) || i.value() == "";
        }else
        {
            ret = (index.data().toString().toLower().contains(i.value().toLower()));
        }

        if(i.value().startsWith("|Number|:"))
        {
            QString numbers = i.value();
            numbers = numbers.replace(0,9,"");
            QStringList number = numbers.split(" ");
            ret = index.data().toInt() >= number.at(0).toInt();
            if(number.size() > 1)
            {
                std::cout << ret;
                ret = index.data().toInt() >= number.at(0).toInt() && index.data().toInt() <= number.at(1).toInt();
            }
        }

        if(!ret)
        {
            return ret;
        }
        else
        {
            for(int i = 0; i < relationColumn.size(); i++)
            {
                QString data = sourceModel()->index(sourceRow, relationColumn[i], sourceParent).data().toString();
                if(data == "")
                {
                    ret = false;
                }
            }
        }
    }
    return ret;
}}
