#ifndef CTOPRELATION_H
#define CTOPRELATION_H

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
class CToPRelation;
}

class CToPRelation : public QDialog
{
    Q_OBJECT

public:
    explicit CToPRelation(QWidget *parent = 0);
    ~CToPRelation();

private slots:
    void on_input_searchPerson_textEdited(const QString &arg1);

    void on_input_searchBornFrom_textEdited(const QString &arg1);

    void on_input_searchBornTo_textEdited(const QString &arg1);

    void on_input_searchDiedFrom_textEdited(const QString &arg1);

    void on_input_searchDiedTo_textEdited(const QString &arg1);

    void on_button_advSearchPerson_released();

private:
    Ui::CToPRelation *ui;
    void searchPerson();
    int showAdvSearchPersons;
    QSqlRelationalTableModel* personModel;
    void loadPersonTable();

    QSortFilterProxyModel *proxyPersonModel = new QSortFilterProxyModel(this);
    QSortFilterProxyModel *proxyCompModel = new QSortFilterProxyModel(this);

    Domain domain;
};

#endif // CTOPRELATION_H
