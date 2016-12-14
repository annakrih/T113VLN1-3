#include "ctoprelation.h"
#include "ui_ctoprelation.h"

CToPRelation::CToPRelation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CToPRelation)
{
    ui->setupUi(this);
    showAdvSearchPersons = 0;
    ui->widget_advancedSearchPerson->setVisible(showAdvSearchPersons);

    personModel = domain.getPersonModel();
    loadPersonTable();
    proxyPersonModel->setDynamicSortFilter(true);
}

CToPRelation::~CToPRelation()
{
    delete ui;
}

void CToPRelation::searchPerson()
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
    loadPersonTable();
}

void CToPRelation::on_input_searchPerson_textEdited(const QString &arg1)
{
    searchPerson();
}

void CToPRelation::on_input_searchBornFrom_textEdited(const QString &arg1)
{
    searchPerson();
}

void CToPRelation::on_input_searchBornTo_textEdited(const QString &arg1)
{
    searchPerson();
}

void CToPRelation::on_input_searchDiedFrom_textEdited(const QString &arg1)
{
    searchPerson();
}

void CToPRelation::on_input_searchDiedTo_textEdited(const QString &arg1)
{
    searchPerson();
}

void CToPRelation::on_button_advSearchPerson_released()
{
    //ToDo
    //showAdvSearchComps = !showAdvSearchComps;
   // ui->widget_advancedSearchComp->setVisible(showAdvSearchComps);
}

void CToPRelation::loadPersonTable()
{
    proxyPersonModel->setSourceModel(personModel);
    ui->table_Person->setModel(proxyPersonModel);
    ui->table_Person->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->table_Person->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->table_Person->verticalHeader()->hide();
    ui->table_Person->setColumnHidden(0,true);

    connect(ui->table_Person,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(personRightClick(QPoint)));
}
