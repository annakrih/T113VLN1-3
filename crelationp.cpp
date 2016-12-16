#include "crelationp.h"
#include "ui_crelationp.h"
#include <QIntValidator>

#include <iostream>

CRelationP::CRelationP(CustomProxyModel *model, QList<int> relList, int id, QMap<QString,int> tList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRelationP)
{
    ui->setupUi(this);
    ui->buttonBox->buttons().first()->setText("Add");
    ui->table_Comp->setModel(model);
    ui->table_Comp->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_Comp->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_Comp->verticalHeader()->hide();
    ui->table_Comp->setColumnHidden(0,true);

    proxyCompModel = model;

    hideRows(ui->table_Comp,relList);

    ui->input_searchBuildYearFrom->setValidator(new QIntValidator);
    ui->input_searchBuildYearTo->setValidator(new QIntValidator);
    ui->input_searchDesignYearFrom->setValidator(new QIntValidator);
    ui->input_searchDesignYearTo->setValidator(new QIntValidator);

    fillComputerTypeSearchBox(tList);

    showAdvSearchComps = 0;
    ui->frame_advSearchComp->setVisible(showAdvSearchComps);

    personId = id;

    connect(
      ui->table_Comp->selectionModel(),
      SIGNAL(currentRowChanged(const QModelIndex&,const QModelIndex&)),
      SLOT(onPersonSelectionChange(const QModelIndex&,const QModelIndex&))
     );
}

CRelationP::~CRelationP()
{
    delete ui;
}

void CRelationP::on_buttonBox_accepted()
{
    QModelIndexList selList = ui->table_Comp->selectionModel()->selectedRows();
    QList<int> idList;

    for(int i = 0; i < selList.size(); i++)
    {
        int row = selList[i].row();
        idList.push_back(ui->table_Comp->model()->index(row,0).data().toInt());
    }

    emit this->addPRelAccepted(idList, personId);
}

void CRelationP::on_buttonBox_rejected()
{
    emit this->relationRejected();
}

void CRelationP::on_CRelationP_finished()
{
    emit this->relationRejected();
}

void CRelationP::on_table_Comp_clicked(const QModelIndex &index)
{

    if(lastSelection == index.row() && !overrideTableClick)
    {
        overrideOnSelectionChange = true;
        ui->table_Comp->selectionModel()->clearSelection();
        lastSelection = -1;
        overrideOnSelectionChange = false;

    }
    else if(!overrideTableClick)
    {
        int index = ui->table_Comp->currentIndex().row();
        lastSelection = index;
    }
    overrideTableClick = false;

}

void CRelationP::onPersonSelectionChange(const QModelIndex &c,const QModelIndex &p)
{
    if(!overrideOnSelectionChange)
    {
        int index = c.row();
        lastSelection = index;
        overrideTableClick = true;
    }
}

void CRelationP::hideRows(QTableView* table, QList<int> rowsToHide)
{

    for(int i = 0; i < table->model()->rowCount(); i++ ){
        int id = table->model()->index(i,0).data().toInt();

        if(rowsToHide.contains(id))
        {
            table->hideRow(i);
        }
        else
        {
            table->showRow(i);
        }
    }
}

void CRelationP::fillComputerTypeSearchBox(QMap<QString,int> compTypeList)
{
    ui->input_searchCompType->addItem("",0);
    QMapIterator<QString,int> i(compTypeList);
    while(i.hasNext())
    {
        i.next();
        ui->input_searchCompType->addItem(i.key(), i.value());
    }
}

void CRelationP::on_button_advSearchComp_released()
{
    if(showAdvSearchComps)
    {
        ui->input_searchCompType->setCurrentIndex(0);
        ui->input_searchDesignYearFrom->clear();
        ui->input_searchDesignYearTo->clear();
        ui->input_searchBuildYearFrom->clear();
        ui->input_searchBuildYearTo->clear();
    }

    showAdvSearchComps = !showAdvSearchComps;
    ui->frame_advSearchComp->setVisible(showAdvSearchComps);
    searchCompModel();
}

void CRelationP::searchCompModel()
{
    QList<int> lst;
    lst.append(1);
    QString name = ui->searchInput_Comp->text();
    QString DYfrom = "";
    QString DYto = "";
    QString BYfrom = "";
    QString BYto = "";
    QString compType = "";
    QString searchDY = "";
    QString searchBY = "";

    if(showAdvSearchComps)
    {
        lst.append(2);
        compType = ui->input_searchCompType->currentText();
        lst.append(3);
        DYfrom = ui->input_searchDesignYearFrom->text();
        DYto = ui->input_searchDesignYearTo->text();
        if(DYfrom != "" || DYto != ""){
            searchDY = "|Number|:";
            DYfrom != ""? searchDY.append(DYfrom): searchDY.append("0");
            if(DYto != ""){
                searchDY.append(" ").append(DYto);
            }
        }
        lst.append(4);
        BYfrom = ui->input_searchBuildYearFrom->text();
        BYto = ui->input_searchBuildYearTo->text();
        if(BYfrom != "" || BYto != ""){
            searchBY = "|Number|:";
            BYfrom != ""? searchBY.append(BYfrom): searchBY.append("0");
            if(BYto != ""){
                searchBY.append(" ").append(BYto);
            }
        }
    }

    proxyCompModel->setFilterKeyColumns(lst);
    proxyCompModel->addFilterFixedString(1, name);
    if(showAdvSearchComps){
        proxyCompModel->addFilterFixedString(2, compType);
        proxyCompModel->addFilterFixedString(3, searchDY);
        proxyCompModel->addFilterFixedString(4, searchBY);
    }
    proxyCompModel->invalidate();

    ui->table_Comp->hideColumn(0);
}

void CRelationP::on_input_searchDesignYearFrom_editingFinished()
{
    searchCompModel();
}

void CRelationP::on_input_searchDesignYearTo_editingFinished()
{
    searchCompModel();
}

void CRelationP::on_input_searchBuildYearFrom_editingFinished()
{
    searchCompModel();
}

void CRelationP::on_input_searchBuildYearTo_editingFinished()
{
    searchCompModel();
}




