#ifndef CRELATIONP_H
#define CRELATIONP_H
#include "domain.h"
#include "customproxymodel.h"

#include <QDialog>
#include <QTableView>

namespace Ui
{
    //class for "add Person Relation" window dialog
    class CRelationP;
}

class CRelationP : public QDialog
{
    Q_OBJECT

public:
    explicit CRelationP(CustomProxyModel* model, QList<int> relList, int id, QMap<QString,int> tlist, QWidget *parent = 0);
    ~CRelationP();

signals:
    //signals used to communicate with the main window.

    //relationRejected means, no relations added, (cancel or x in the corner)
    void relationRejected();

    //addPRelAccepted sends back parameters to the main window, a list of relation id's to add, and the id to add it to.
    void addPRelAccepted(const QList<int> &, const int &);

private slots:
    //When "Add" is clicked the function adds the selected computers to the person as a relation
    void on_buttonBox_accepted();

    //emits the signal that the window has been closed, without making any changes
    void on_buttonBox_rejected();  //when user clicks cancel
    void on_CRelationP_finished(); //when the user is closed

    //select and unselects a row in the table
    void on_table_Comp_clicked(const QModelIndex &index);

    //an event that is triggered when the selection is changed
    void onPersonSelectionChange(const QModelIndex &c,const QModelIndex &p);

    //TODO
    void searchCompModel();

    //shows advanced search when the advSearchComp-button is released
    void on_button_advSearchComp_released();

    //Calls the search function to update the computer table after editing is finished in:
    void on_searchInput_Comp_textEdited(const QString &arg1);//name input
    void on_input_searchDesignYearFrom_textEdited(const QString &arg1);//design year from input
    void on_input_searchDesignYearTo_textEdited(const QString &arg1);//design year to input
    void on_input_searchBuildYearFrom_textEdited(const QString &arg1);//build year from input
    void on_input_searchBuildYearTo_textEdited(const QString &arg1);//build year to input
    void on_input_searchCompType_currentIndexChanged(int index);//nationality input

private:
    Ui::CRelationP *ui;

    int lastSelection;
    int personId;

    CustomProxyModel * proxyCompModel;

    bool showAdvSearchComps;
    bool overrideTableClick = 0;
    bool overrideOnSelectionChange = 0;

    void fillComputerTypeSearchBox(QMap<QString,int> compTypeList);
};

#endif // CRELATIONP_H
