#ifndef CUSTOMPROXYMODEL_H
#define CUSTOMPROXYMODEL_H

#include <QSortFilterProxyModel>

//Subclass of QSortFilterProxyModel
//Created by necessity so that we can sort/search without querying the sql database
//doing so would result in loss of unsaved changes (edits/deletes/additions)
class CustomProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CustomProxyModel(QObject *parent = 0);
    //setFilterKeyColumns takes in QList of columns to sort.
    void setFilterKeyColumns(const QList<int> &filterColumns);
    //addFilterFixedString takes in a column, and the filter to be used in the search
    void addFilterFixedString(int column, const QString &pattern);
    //setRelationColumn takes in a list of columns that are used in relations
    //these columns will perform exact searches, and so that filterAcceptsRow doesn't unhide already deleted rows
    void setRelationColumn(QList<int> list);

protected:
    //filterAcceptsrow loops through the columns with filters and shows the rows that pass, and hide the rows that fail.
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    //columnPattern holds a map of columns, and search pattern
    QMap<int, QString> columnPatterns;
    //relationColumn holds QList columns that are foreign keys/relation columns
    QList<int> relationColumn;
};

#endif // CUSTOMPROXYMODEL_H
