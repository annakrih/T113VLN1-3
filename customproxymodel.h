#ifndef CUSTOMPROXYMODEL_H
#define CUSTOMPROXYMODEL_H

#include <QSortFilterProxyModel>

class CustomProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CustomProxyModel(QObject *parent = 0);
    void setFilterKeyColumns(const QList<int> &filterColumns);
    void addFilterFixedString(int column, const QString &pattern);
    void setRelationColumn(QList<int> list);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    QMap<int, QString> columnPatterns;
    QList<int> relationColumn;
};

#endif // CUSTOMPROXYMODEL_H
