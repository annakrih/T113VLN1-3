#ifndef CRELATIONP_H
#define CRELATIONP_H

#include <QDialog>
#include <QSortFilterProxyModel>

namespace Ui {
class CRelationP;
}

class CRelationP : public QDialog
{
    Q_OBJECT

public:
    explicit CRelationP(QSortFilterProxyModel* model,QWidget *parent = 0);
    ~CRelationP();

signals:
    void relationRejected();
    void addPRelAccepted(const QList<int> &);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_CRelationP_finished();

    void on_table_Comp_clicked(const QModelIndex &index);

    void onPersonSelectionChange(const QModelIndex &c,const QModelIndex &p);

private:
    Ui::CRelationP *ui;

    int lastSelection;

    bool overrideTableClick = 0;
    bool overrideOnSelectionChange = 0;
};

#endif // CRELATIONP_H
