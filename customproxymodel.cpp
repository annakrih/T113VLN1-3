#include "customproxymodel.h"

#include <iostream>

CustomProxyModel::CustomProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

void CustomProxyModel::setFilterKeyColumns(const QList<int> &filterColumns)
{
    columnPatterns.clear();

    foreach(int column, filterColumns)
    {
        columnPatterns.insert(column, QString());
    }
}

void CustomProxyModel::addFilterFixedString(int column, const QString &pattern)
{
    if(!columnPatterns.contains(column))
    {
        return;
    }

    columnPatterns[column] = pattern;
}

void CustomProxyModel::setRelationColumn(QList<int> list)
{
    relationColumn = list;
}
//special case! id's (column 0 data) to keep hidden
void CustomProxyModel::setDontShow(QList<int> list){
    dontShow = list;
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
        QModelIndex id = sourceModel()->index(sourceRow, 0, sourceParent);
        if(relationColumn.contains(i.key()))
        {
            //if column is a foreign key, use exact search
            ret = (index.data().toString().toLower() == (i.value().toLower())) || i.value() == "";
        }else
        {
            //if column is not foreign key, use "like" search
            ret = (index.data().toString().toLower().contains(i.value().toLower()));
        }

        //special case to search numbers to and from.
        //|Number|: is prepended to all searches in our program that use from/to search.
        if(i.value().startsWith("|Number|:"))
        {
            QString numbers = i.value();
            numbers = numbers.replace(0,9,"");
            QStringList number = numbers.split(" ");
            ret = index.data().toInt() >= number.at(0).toInt();
            if(number.size() > 1)
            {
                ret = index.data().toInt() >= number.at(0).toInt() && index.data().toInt() <= number.at(1).toInt();
            }
        }

        //if row has id in dontShow list, dont show it! forced false.
        if(dontShow.contains(id.data().toInt())){
           ret = false;
        }

        if(!ret)
        {
            return ret;
        }
        else
        {
            //if column is a relationColumn/foreign key .. and it's empty, then it has been deleted.
            //abuse a quirk of QT to detect deleted row. and dont reshow it's broken form.
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
}
