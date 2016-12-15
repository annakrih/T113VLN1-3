#ifndef CRELATIONP_H
#define CRELATIONP_H

#include <QDialog>
#include <QTableView>
#include <QSortFilterProxyModel>

namespace Ui
{
class CRelationP;
}

class CRelationP : public QDialog
{
    Q_OBJECT

public:
    explicit CRelationP(QSortFilterProxyModel* model, QList<int> relList, int id, QWidget *parent = 0);
    ~CRelationP();

signals:
    void relationRejected();
    void addPRelAccepted(const QList<int> &, const int &);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_CRelationP_finished();

    void on_table_Comp_clicked(const QModelIndex &index);

    void onPersonSelectionChange(const QModelIndex &c,const QModelIndex &p);

    void hideRows(QTableView* table, QList<int> rowsToHide);

    void on_button_advSearchComp_released();

private:
    Ui::CRelationP *ui;

    int lastSelection;
    int personId;

    bool showAdvSearch;
    bool overrideTableClick = 0;
    bool overrideOnSelectionChange = 0;
};

#endif // CRELATIONP_H
