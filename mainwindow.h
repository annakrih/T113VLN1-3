#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include "utils.h"
#include "domain.h"
#include <string>
#include <iostream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QWidget>
#include <QTableView>
#include "customproxymodel.h"

#include "personDialog.h"
#include "computerdialog.h"
#include "prelationc.h"
#include "crelationp.h"

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void searchComp();

    void on_comboBox_currentIndexChanged(int index);
    void on_searchComboBox_currentIndexChanged(int index);
    void loadPersonTable();
    void loadCompTable();
    void loadPITable();
    void loadCITable();
    void fillNationalitySearchBox(QMap<QString, int> natList);
    void fillComputerTypeSearchBox(QMap<QString, int> compTypeList);

private slots:

    void on_button_addPerson_clicked();

    void on_button_addcomp_clicked();

    void addPersonDialog();

    //add person icon, when pressed the add person window appears
    void editPersonDialog();

    //add computer icon, when pressed the add computer window appears
    void addComputerDialog();

    void editComputerDialog();

    void on_input_searchPerson_textEdited();

    void on_button_advSearchPerson_released();

    void on_checkBox_searchFemale_released();

    void on_checkBox_searchMale_released();

    void on_input_searchNat_currentIndexChanged(const QString &arg1);

    void on_input_searchBornFrom_editingFinished();

    void on_input_searchBornTo_editingFinished();

    void on_input_searchDiedFrom_editingFinished();

    void on_input_searchDiedTo_editingFinished();

    void on_searchInput_Comp_textEdited();

    void on_button_advSearchComp_released();

    void on_input_searchDesignYearFrom_editingFinished();

    void on_input_searchDesignYearTo_editingFinished();

    void on_input_searchBuildYearFrom_editingFinished();

    void on_input_searchBuildYearTo_editingFinished();

    void onDialogRejected();

    void onAddPersonAccepted(const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &imagePlace);

    void onAddComputerAccepted(const QString &n, const int &t, const int &d, const int &b);

    void onEditPersonAccepted(const int &id, const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &imagePlace);

    void onEditComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b);

    void on_actionAdd_new_person_triggered();

    void on_actionEdit_person_triggered();

    void on_actionAdd_new_computer_triggered();

    void on_actionEdit_Computer_triggered();

    void on_actionSave_Changes_triggered();

    void saveChanges();

    void revertChanges();

    void saveModel(QSqlRelationalTableModel * model);

    void personRightClick();

    void computerRightClick();

    void deleteSelected();

    void on_actionDelete_triggered();

    QList<int> getPersonRelationId(int id);

    QList<int> getComputerRelationId(int id);

    void hideAllRowsExcept(QTableView* table, QList<int> rowsNotToHide);

    void loadPersonInfo();

    void loadComputerInfo();

    void on_actionPersons_2_triggered();

    void on_actionComputers_2_triggered();

    void on_actionRelations_triggered();

    void on_input_searchCompType_currentIndexChanged(const QString &arg1);

    void on_pushButton_editSelectedEntry_pressed();

    void on_pushButton_Delete_released();

    void on_addPersonRelation_released();

    void onAddPRelAccepted(const QList<int> &l, const int &id);

    void onAddCRelAccepted(const QList<int> &l, const int &id);

    void on_addComputerRelation_released();

    void on_tabsWidget_personComputer_tabBarClicked(int index);

    void clearAllSelection();

    void on_pushButton_Revert_released();

    void on_table_Person_clicked(const QModelIndex &index);

    void onPersonSelectionChange(const QModelIndex &c, const QModelIndex &p);

    void on_table_Comp_clicked(const QModelIndex &index);

    void onCompSelectionChange(const QModelIndex &c, const QModelIndex &p);

    void closeEvent();

    void on_deletePersonRelation_released();

    void deleteSelectedRelations();

    void buttonEnabledFunct();

private:
    Ui::MainWindow *ui;
    PersonDialog *personDialogWindow;
    ComputerDialog *computerDialogWindow;
    CRelationP* pRelDialogWindow;
    PRelationC* cRelDialogWindow;

    Domain domain;

    int nextPersonId = 0;
    int nextComputerId = 0;

    QSqlRelationalTableModel* personModel;
    QSqlRelationalTableModel* computerModel;
    QSqlRelationalTableModel* relationModel;

    CustomProxyModel *proxyPersonModel = new CustomProxyModel(this);
    CustomProxyModel *proxyCompModel = new CustomProxyModel(this);
    CustomProxyModel *proxyPIModel = new CustomProxyModel(this);
    CustomProxyModel *proxyCIModel = new CustomProxyModel(this);

    int currentPersonSearchIndex = 0;
    int currentCompSearchIndex = 0;

    bool showAdvSearchPersons = 0;
    bool showAdvSearchComps = 0;

    int lastPersonSelection = 0;
    int lastCompSelection = 0;

    bool overrideOnPersonSelectionChange = 0;
    bool overrideOnCompSelectionChange = 0;
    bool overrideTableClick = 0;

    bool changesMade = 0;


    void searchPersonModel();
    void searchCompModel();
};

#endif // MAINWINDOW_H
