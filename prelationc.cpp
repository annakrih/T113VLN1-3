#include "prelationc.h"
#include "ui_prelationc.h"
#include "domain.h"

PRelationC::PRelationC(CustomProxyModel *model, QList<int> relList, int id, QMap<QString,int> natList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PRelationC)
{
    ui->setupUi(this);

    ui->input_searchBornFrom->setValidator(new QIntValidator);
    ui->input_searchBornTo->setValidator(new QIntValidator);
    ui->input_searchDiedFrom->setValidator(new QIntValidator);
    ui->input_searchDiedTo->setValidator(new QIntValidator);

    showAdvSearchPersons = 0;
    ui->widget_advancedSearchPerson->setVisible(showAdvSearchPersons);

    fillNationalitySearchBox(natList);

    proxyPersonModel = model;

    ui->buttonBox->buttons().first()->setText("Add");
    ui->table_Person->setModel(proxyPersonModel);
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
}

PRelationC::~PRelationC()
{
    delete ui;
}

void PRelationC::searchPersonModel()
{
    QList<int> lst;
    lst.append(1);
    QString name = ui->input_searchPerson->text();
    QString gender = "";
    QString nationality = "";
    QString BYfrom = "";
    QString BYto = "";
    QString searchBY = "";
    QString DYfrom = "";
    QString DYto = "";
    QString searchDY = "";

    if(showAdvSearchPersons)
    {
        lst.append(2);
        if(ui->checkBox_searchFemale->isChecked())
        {
            gender = "Female";
        }
        else if(ui->checkBox_searchMale->isChecked())
        {
            gender = "Male";
        }
        lst.append(3);
        nationality = ui->input_searchNat->currentText();
        lst.append(4);
        BYfrom = ui->input_searchBornFrom->text();
        BYto = ui->input_searchBornTo->text();
        if(BYfrom != "" || BYto != ""){
            searchBY = "|Number|:";
            BYfrom != ""? searchBY.append(BYfrom): searchBY.append("0");
            if(BYto != ""){
                searchBY.append(" ").append(BYto);
            }
        }
        lst.append(5);
        DYfrom = ui->input_searchDiedFrom->text();
        DYto = ui->input_searchDiedTo->text();
        if(DYfrom != "" || DYto != ""){
            searchBY = "|Number|:";
            DYfrom != ""? searchBY.append(DYfrom): searchBY.append("0");
            if(DYto != ""){
                searchBY.append(" ").append(DYto);
            }
        }
    }
    proxyPersonModel->setFilterKeyColumns(lst);
    proxyPersonModel->addFilterFixedString(1, name);
    if(showAdvSearchPersons)
    {
        proxyPersonModel->addFilterFixedString(2, gender);
        proxyPersonModel->addFilterFixedString(3, nationality);
        proxyPersonModel->addFilterFixedString(4, searchBY);
        proxyPersonModel->addFilterFixedString(5, searchDY);
    }
    proxyPersonModel->invalidate();

    ui->table_Person->hideColumn(0);
    ui->table_Person->hideColumn(6);
}

void PRelationC::on_input_searchPerson_textEdited()
{
    searchPersonModel();
}

void PRelationC::on_input_searchBornFrom_textEdited()
{
    searchPersonModel();
}

void PRelationC::on_input_searchBornTo_textEdited()
{
    searchPersonModel();
}

void PRelationC::on_input_searchDiedFrom_textEdited()
{
    searchPersonModel();
}

void PRelationC::on_input_searchDiedTo_textEdited()
{
    searchPersonModel();
}

void PRelationC::on_button_advSearchPerson_released()
{
    if(showAdvSearchPersons)
    {
        ui->input_searchNat->setCurrentIndex(0);

        ui->checkBox_searchFemale->setChecked(false);
        ui->checkBox_searchMale->setChecked(false);
        ui->input_searchBornFrom->clear();
        ui->input_searchBornTo->clear();
        ui->input_searchDiedFrom->clear();
        ui->input_searchDiedTo->clear();
        ui->input_searchBornFrom->setCursorPosition(0);
    }
    showAdvSearchPersons = !showAdvSearchPersons;
    ui->widget_advancedSearchPerson->setVisible(showAdvSearchPersons);
    searchPersonModel();
}

void PRelationC::on_buttonBox_accepted()
{
    QModelIndexList selList = ui->table_Person->selectionModel()->selectedRows();
    QList<int> idList;

    for(int i = 0; i < selList.size(); i++)
    {
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
    }
    else if(!overrideTableClick)
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


void PRelationC::hideRows(QTableView* table, QList<int> rowsToHide)
{
    for(int i = 0; i < table->model()->rowCount(); i++ )
    {
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

void PRelationC::fillNationalitySearchBox(QMap<QString,int> natList)
{
    ui->input_searchNat->addItem("",0);
    QMapIterator<QString, int> i(natList);
    while (i.hasNext())
    {
        i.next();
        ui->input_searchNat->addItem(i.key(),i.value());
    }
}

void PRelationC::on_checkBox_searchFemale_released()
{
    ui->checkBox_searchMale->setChecked(false);
    searchPersonModel();
}

void PRelationC::on_checkBox_searchMale_released()
{
    ui->checkBox_searchFemale->setChecked(false);
    searchPersonModel();
}
