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

    //functions that loads table model, and sets settings
    void loadPersonTable();
    void loadCompTable();
    void loadPITable();
    void loadCITable();

    //function that fills nationality combobox with countries (from db)
    void fillNationalitySearchBox(QMap<QString, int> natList);

    //function that fills computer type combo box with computer types (from db)
    void fillComputerTypeSearchBox(QMap<QString, int> compTypeList);

private slots:

    //triggers when "add Person" button is pressed
    //calls addPersonDialog()
    void on_button_addPerson_clicked();

    //triggers when "add computer" button is pressed
    //calls addComputerDialog()
    void on_button_addcomp_clicked();

    //calls the personDialog window:
    void addPersonDialog();
    void editPersonDialog();

    //calls the computerDialog window:
    void addComputerDialog();
    void editComputerDialog();

    //shows/hides the advanced search for person
    void on_button_advSearchPerson_released();

    //calls searchPersonModel to update the table with the search results on these triggers:
    void on_input_searchPerson_textEdited();
    void on_input_searchNat_currentIndexChanged(const QString &arg1);
    void on_input_searchBornFrom_editingFinished();
    void on_input_searchBornTo_editingFinished();
    void on_input_searchDiedFrom_editingFinished();
    void on_input_searchDiedTo_editingFinished();

    //calls the searchPersonModel and unchecks the other gender so only 1 gender can be checked
    //this allows us to uncheck both boxes, unlike radio buttons where its one or the other.
    void on_checkBox_searchFemale_released();
    void on_checkBox_searchMale_released();

    //shows/hides the advanced search for computer
    void on_button_advSearchComp_released();

    //calls searchComputerModel to update the table with the searchresults on these triggers:
    void on_searchInput_Comp_textEdited();
    void on_input_searchDesignYearFrom_editingFinished();
    void on_input_searchDesignYearTo_editingFinished();
    void on_input_searchBuildYearFrom_editingFinished();
    void on_input_searchBuildYearTo_editingFinished();
    void on_input_searchCompType_currentIndexChanged(const QString &arg1);

    //run when any of the dialog/popup windows cancel or close
    void onDialogRejected();

    //onAddPersonAccepted triggered by personDialog window
    //adds record of new person into model
    void onAddPersonAccepted(const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &imagePlace);

    //onAddComputerAccepted triggered by personDialog window
    //adds record of new computer into model
    void onAddComputerAccepted(const QString &n, const int &t, const int &d, const int &b);

    //onEditPersonAccepted triggered by computerDialog window
    //changes record of person in model
    void onEditPersonAccepted(const int &id, const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &imagePlace);

    //onEditComputerAccepted triggered by computerDialog window
    //changes record of computer in model
    void onEditComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b);

    //QT actions, that call other functions when triggered/clicked self explanatory
    void on_actionAdd_new_person_triggered();
    void on_actionEdit_person_triggered();
    void on_actionAdd_new_computer_triggered();
    void on_actionEdit_Computer_triggered();
    void on_actionSave_Changes_triggered();
    void on_actionDelete_triggered();
    void on_actionDeleteAllPersons_triggered();
    void on_actionDeleteAllComputers_triggered();
    void on_actionDeleteAllRelations_triggered();
    void on_actionReset_to_default_database_triggered();
    void on_actionDelete_relation_triggered();

    //function that saves changes to the models into the database
    void saveChanges();

    //function that reverts changes made to the model
    void revertChanges();

    //mini function that saves changes to a specific model to the database
    void saveModel(QSqlRelationalTableModel * model);

    //function that is triggered on a rightclick on the person table.
    //displays a customcontextmenu (right click menu)
    void personRightClick();

    //function that is triggered on a rightclick on the computer table.
    //displays a customcontextmenu (right click menu)
    void computerRightClick();

    //function that is triggered on a rightclick on the person info table. (personid to computer relations)
    //displays a customcontextmenu (right click menu)
    void PIRightClick();

    //function that is triggered on a rightclick on the computer info table. (computerid to person relations)
    //displays a customcontextmenu (right click menu)
    void CIRightClick();

    //a super function that deletes selected rows from a table based on the current tab open (person or computer)
    void deleteSelected();

    //getPersonRelationId returns a QList of computerId's that a specific person has relations to
    QList<int> getPersonRelationId(int id);

    //getComputerRelationId returns a QList of personId's that a specific computer has relations to
    QList<int> getComputerRelationId(int id);

    //a function that hides all rows in a table, except rows that match a QList of id's (column 0 data)
    void hideAllRowsExcept(QTableView* table, QList<int> rowsNotToHide);

    //load info about selected person into the right side view (person info)
    void loadPersonInfo();

    //load info about selected computer into the right side view (computer info)
    void loadComputerInfo();

    //a helper function that makes sure that the side view is displayed or hidden correctly, after deleteAll functions (example : person info)
    void sideViewCheck();

    //calls editpersonDialog() on click
    void on_pushButton_editSelectedEntry_pressed();

    //calls deletedSelected on click
    void on_pushButton_Delete_released();

    //opens a add person relation window, used to add relations to person
    void on_addPersonRelation_released();

    //triggered by CRelationP, returns personid, and a list of computer id's to add relations to.
    void onAddPRelAccepted(const QList<int> &l, const int &id);

    //triggered by PRelationC, returns personid, and a list of computer id's to add relations to.
    void onAddCRelAccepted(const QList<int> &l, const int &id);

    //opens a add computer relation window, used to add relations to computer
    void on_addComputerRelation_released();

    //triggered when tabs are changed (person, computer)
    void on_tabsWidget_personComputer_tabBarClicked(int index);

    //helper function to clear all table selections
    void clearAllSelection();

    //triggers revertChanges on click
    void on_pushButton_Revert_released();

    //special functions to ensure that the table selections work as intended.
    //drag to select many, click to select one, click again to deselect.
    void on_table_Person_clicked(const QModelIndex &index);
    void onPersonSelectionChange(const QModelIndex &c, const QModelIndex &p);
    void on_table_Comp_clicked(const QModelIndex &index);
    void onCompSelectionChange(const QModelIndex &c, const QModelIndex &p);
    void onPISelectionChange(const QModelIndex &c,const QModelIndex &p);
    void on_tablePI_clicked(const QModelIndex &index);
    void on_tableCI_clicked(const QModelIndex &index);
    void onCISelectionChange(const QModelIndex &c,const QModelIndex &p);

    //event that runs on mainWindow close, (prompts user to save if unsaved changes exist)
    void closeEvent(QCloseEvent *event);

    //buttons that trigger deleteSelectedRelations on click
    void on_deletePersonRelation_released();
    void on_deleteComputerRelation_released();

    //a super function that deletes selected relation rows from a table based on the current tab open (person or computer)
    void deleteSelectedRelations();

    //super function that ensures that buttons are in the right state, (disabled/enabled)
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
    int lastPISelection = 0;
    int lastCISelection = 0;

    bool overrideOnPersonSelectionChange = 0;
    bool overrideOnCompSelectionChange = 0;
    bool overrideOnCISelectionChange = 0;
    bool overrideOnPISelectionChange = 0;

    bool overrideTableClick = 0;

    bool changesMade = 0;


    void searchPersonModel();
    void searchCompModel();
};

#endif // MAINWINDOW_H
