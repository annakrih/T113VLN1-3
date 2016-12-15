#ifndef PRELATIONC_H
#define PRELATIONC_H

#include "utils.h"
#include <QSortFilterProxyModel>
#include <QModelIndexList>

#include <QDialog>

namespace Ui
{
class PRelationC;
}

class PRelationC : public QDialog
{
    Q_OBJECT

public:
    explicit PRelationC(QSortFilterProxyModel* model,QWidget *parent = 0);
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

signals:
    void relationRejected();
    void addCRelAccepted(const QList<int> &l);


private:
    Ui::PRelationC *ui;
    void searchPerson();
    int showAdvSearchPersons;
    int lastSelection;

    bool overrideTableClick = 0;
    bool overrideOnSelectionChange = 0;


    //Domain domain;
};

#endif // PRELATIONC_H
