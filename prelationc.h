#ifndef PRELATIONC_H
#define PRELATIONC_H

#include "utils.h"
#include <QDialog>
#include <QTableView>
#include "domain.h"
#include "customproxymodel.h"

namespace Ui
{
    class PRelationC;
}

class PRelationC : public QDialog
{
    Q_OBJECT

public:
    explicit PRelationC(CustomProxyModel* model, QList<int> relList, int id, QMap<QString,int> natList, QWidget *parent = 0);
    ~PRelationC();

private slots:
    //hides/showes the advanced search when the advanced search button is clicked
    void on_button_advSearchPerson_released();

    //The search is updated on these triggers:
    void on_input_searchPerson_textEdited();
    void on_input_searchBornFrom_textEdited();
    void on_input_searchBornTo_textEdited();
    void on_input_searchDiedFrom_textEdited();
    void on_input_searchDiedTo_textEdited();
    //if one checkBox is checked the other is unchecked and the search updated:
    void on_checkBox_searchFemale_released();
    void on_checkBox_searchMale_released();

    //adds the selected person to the computer by relation when "Add" is clicked
    void on_buttonBox_accepted();

    //emits the signal that the window has been closed without making any changes to the database
    void on_buttonBox_rejected(); //when the user clicks cancel
    void on_PRelationC_finished(); //when the user closes the window

    //selects and unselects a row in the table
    void on_table_Person_clicked(const QModelIndex &index);

    //an event that is triggered when the selection is changed
    void onPersonSelectionChange(const QModelIndex &c,const QModelIndex &p);

    //hides rows in the table that should not be visible
    void hideRows(QTableView* table, QList<int> rowsToHide);

signals:
    void relationRejected();
    void addCRelAccepted(const QList<int> &l, const int &);

private:
    Ui::PRelationC *ui;
    CustomProxyModel *proxyPersonModel;
    void searchPersonModel();
    void fillNationalitySearchBox(QMap<QString,int> natList);

    int showAdvSearchPersons;
    int lastSelection;
    int computerId;

    bool overrideTableClick = 0;
    bool overrideOnSelectionChange = 0;
};

#endif // PRELATIONC_H
