#ifndef PRELATIONC_H
#define PRELATIONC_H

#include "utils.h"
#include <QDialog>
#include <QTableView>
#include <QSortFilterProxyModel>
#include "domain.h"

namespace Ui
{
class PRelationC;
}

class PRelationC : public QDialog
{
    Q_OBJECT

public:
    explicit PRelationC(QSortFilterProxyModel* model, QList<int> relList, int id, QWidget *parent = 0);
    ~PRelationC();

private slots:
    void on_input_searchPerson_textEdited();

    void on_input_searchBornFrom_textEdited();

    void on_input_searchBornTo_textEdited();

    void on_input_searchDiedFrom_textEdited();

    void on_input_searchDiedTo_textEdited();

    void on_button_advSearchPerson_released();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_PRelationC_finished();

    void on_table_Person_clicked(const QModelIndex &index);

    void onPersonSelectionChange(const QModelIndex &c,const QModelIndex &p);

    void hideRows(QTableView* table, QList<int> rowsToHide);

signals:
    void relationRejected();
    void addCRelAccepted(const QList<int> &l, const int &);


private:
    Ui::PRelationC *ui;
    void searchPerson();
    int showAdvSearchPersons;
    int lastSelection;

    QSqlRelationalTableModel* personModel;

    int computerId;

    Domain domain;

    bool overrideTableClick = 0;
    bool overrideOnSelectionChange = 0;


    //Domain domain;
};

#endif // PRELATIONC_H
