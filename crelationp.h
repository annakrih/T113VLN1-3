#ifndef CRELATIONP_H
#define CRELATIONP_H
#include "domain.h"
#include "customproxymodel.h"

#include <QDialog>
#include <QTableView>

namespace Ui
{
    class CRelationP;
}

class CRelationP : public QDialog
{
    Q_OBJECT

public:
    explicit CRelationP(CustomProxyModel* model, QList<int> relList, int id, QMap<QString,int> tlist, QWidget *parent = 0);
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

    void searchCompModel();

    //shows advanced search when the advSearchComp-button is released
    void on_button_advSearchComp_released();

    //Calls the search function to update the computer table after editing is finished in:
    void on_input_searchDesignYearFrom_editingFinished(); //design year from input
    void on_input_searchDesignYearTo_editingFinished();   //design year to input
    void on_input_searchBuildYearFrom_editingFinished();  //build year from input
    void on_input_searchBuildYearTo_editingFinished();    //build year to input

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
