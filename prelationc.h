#ifndef PRELATIONC_H
#define PRELATIONC_H

#include <vector>
#include "utils.h"
#include "domain.h"
#include <string>
#include <iostream>
#include <QMessageBox>

#include "personDialog.h"
#include "computerdialog.h"

#include <QDialog>

namespace Ui
{
class PRelationC;
}

class PRelationC : public QDialog
{
    Q_OBJECT

public:
    explicit PRelationC(QWidget *parent = 0);
    ~PRelationC();

private slots:
    void on_input_searchPerson_textEdited();

    void on_input_searchBornFrom_textEdited();

    void on_input_searchBornTo_textEdited();

    void on_input_searchDiedFrom_textEdited();

    void on_input_searchDiedTo_textEdited();

    void on_button_advSearchPerson_released();

private:
    Ui::PRelationC *ui;
    void searchPerson();
    int showAdvSearchPersons;
    QSqlRelationalTableModel* personModel;
    void loadPersonTable();

    QSortFilterProxyModel *proxyPersonModel = new QSortFilterProxyModel(this);
    QSortFilterProxyModel *proxyCompModel = new QSortFilterProxyModel(this);

    Domain domain;
};

#endif // PRELATIONC_H
