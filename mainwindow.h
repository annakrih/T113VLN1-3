#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include "utils.h"
#include "domain.h"
#include <string>
#include <iostream>
#include <QMessageBox>

#include "personDialog.h"
#include "computerdialog.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void on_comboBox_currentIndexChanged(int index);
    void on_searchComboBox_currentIndexChanged(int index);
    void loadPersonTable();
    void loadCompTable();
    void fillNationalitySearchBox(QMap<QString, int> natList);

private slots:
    void addPersonDialog();

    void editPersonDialog();

    void addComputerDialog();

    void editComputerDialog();

    void on_input_searchPerson_textEdited();

    void on_searchInput_Comp_textEdited(const QString &searchString);

    void on_button_advSearchPerson_released();

    void on_checkBox_searchFemale_released();

    void on_checkBox_searchMale_released();

    void on_input_searchBornFrom_editingFinished();

    void on_input_searchBornTo_editingFinished();

    void on_input_searchDiedFrom_editingFinished();

    void on_input_searchDiedTo_editingFinished();

    void on_table_Person_clicked(const QModelIndex &index);

    void onPersonSelectionChange();

    void on_table_Comp_clicked(const QModelIndex &index);

    void onCompSelectionChange();

    void on_actionAdd_new_person_triggered();

    void onPersonRejected();

    void onComputerRejected();

    void onAddPersonAccepted(const QString &n, const int &g, const int &nat, const int &b, const int &d);

    void onAddComputerAccepted(const QString &n, const int &t, const int &d, const int &b);

    void onEditPersonAccepted(const int &id, const QString &n, const int &g, const int &nat, const int &b, const int &d);    

    void onEditComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b);

    void on_actionEdit_person_triggered();

<<<<<<< HEAD
    void on_actionAdd_new_computer_triggered();

    void on_actionEdit_Computer_triggered();
=======
    void on_input_searchNat_currentIndexChanged(const QString &nat);
>>>>>>> origin/master

private:
    Ui::MainWindow *ui;
    PersonDialog *personDialogWindow;
    ComputerDialog *computerDialogWindow;

    QSortFilterProxyModel *proxyPersonModel = new QSortFilterProxyModel(this);
    QSortFilterProxyModel *proxyCompModel = new QSortFilterProxyModel(this);

    int currentPersonSearchIndex = 0;
    int currentCompSearchIndex = 0;

    bool showAdvSearchPersons = 0;
    int lastPersonSelection = 0;
    int lastCompSelection = 0;

    //bool showAdvSearchComps = 0;
    bool overrideOnPersonSelectionChange = 0;
    bool overrideOnCompSelectionChange = 0;

    Domain domain;

    QSqlRelationalTableModel* personModel;
    QSqlRelationalTableModel* computerModel;

    void searchPerson();
    void searchComp(const QString& searchInput);

};

#endif // MAINWINDOW_H
