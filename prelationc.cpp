#include "prelationc.h"
#include "ui_prelationc.h"
#include "domain.h"

PRelationC::PRelationC(QSortFilterProxyModel *model, QList<int> relList, int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PRelationC)
{
    ui->setupUi(this);
    showAdvSearchPersons = 0;
    ui->widget_advancedSearchPerson->setVisible(showAdvSearchPersons);

    ui->buttonBox->buttons().first()->setText("Add");
    ui->table_Person->setModel(model);
    ui->table_Person->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_Person->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_Person->verticalHeader()->hide();
    ui->table_Person->setColumnHidden(0,true);
    ui->table_Person->setColumnHidden(6,true);

    hideRows(ui->table_Person,relList);

    computerId = id;

    connect(
      ui->table_Person->selectionModel(),
      SIGNAL(currentRowChanged(const QModelIndex&,const QModelIndex&)),
      SLOT(onPersonSelectionChange(const QModelIndex&,const QModelIndex&))
     );

    //connect(ui->table_Person,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(personRightClick(QPoint)));
}

PRelationC::~PRelationC()
{
    delete ui;
}

void PRelationC::searchPerson()
{
    QString searchInput = ui->input_searchPerson->text();

    if(showAdvSearchPersons)
    {
        QString gender = "0";

        if(ui->checkBox_searchFemale->isChecked())
        {
            gender = "2";
        }
        else if(ui->checkBox_searchMale->isChecked())
        {
            gender = "1";
        }
        QString BYfrom = ui->input_searchBornFrom->text();
        QString BYto = ui->input_searchBornTo->text();
        QString DYfrom = ui->input_searchDiedFrom->text();
        QString DYto = ui->input_searchDiedTo->text();
        QString nationality = ui->input_searchNat->itemData(ui->input_searchNat->currentIndex()).toString();

        personModel = domain.searchPerson(searchInput, gender, BYfrom, BYto, DYfrom, DYto, nationality);
    }
    else
    {
        personModel = domain.searchPerson(searchInput);
    }
}

void PRelationC::on_input_searchPerson_textEdited()
{
    searchPerson();
}

void PRelationC::on_input_searchBornFrom_textEdited()
{
    searchPerson();
}

void PRelationC::on_input_searchBornTo_textEdited()
{
    searchPerson();
}

void PRelationC::on_input_searchDiedFrom_textEdited()
{
    searchPerson();
}

void PRelationC::on_input_searchDiedTo_textEdited()
{
    searchPerson();
}

void PRelationC::on_button_advSearchPerson_released()
{
    //ToDo
    //showAdvSearchComps = !showAdvSearchComps;
   // ui->widget_advancedSearchComp->setVisible(showAdvSearchComps);
}

void PRelationC::on_buttonBox_accepted()
{
    QModelIndexList selList = ui->table_Person->selectionModel()->selectedRows();
    QList<int> idList;

    for(int i = 0; i < selList.size(); i++){
        int row = selList[i].row();
        idList.push_back(ui->table_Person->model()->index(row,0).data().toInt());
    }

    emit this->addCRelAccepted(idList, computerId);
}

void PRelationC::on_buttonBox_rejected()
{
    emit this->relationRejected();
}

void PRelationC::on_PRelationC_finished()
{
    emit this->relationRejected();
}


void PRelationC::on_table_Person_clicked(const QModelIndex &index)
{

    if(lastSelection == index.row() && !overrideTableClick)
    {
        overrideOnSelectionChange = true;
        ui->table_Person->selectionModel()->clearSelection();
        lastSelection = -1;
        overrideOnSelectionChange = false;

    }else if(!overrideTableClick)
    {
        int index = ui->table_Person->currentIndex().row();
        lastSelection = index;
    }
    overrideTableClick = false;

}

void PRelationC::onPersonSelectionChange(const QModelIndex &c,const QModelIndex &p)
{
    if(!overrideOnSelectionChange)
    {
        int index = c.row();
        lastSelection = index;
        overrideTableClick = true;
    }
}

void PRelationC::hideRows(QTableView* table, QList<int> rowsToHide){

    for(int i = 0; i < table->model()->rowCount(); i++ ){
        int id = table->model()->index(i,0).data().toInt();

        if(rowsToHide.contains(id)){
            table->hideRow(i);
        }else{
            table->showRow(i);
        }
    }
}
