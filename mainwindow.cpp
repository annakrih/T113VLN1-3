#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    personModel = domain.getPersonModel();
    computerModel = domain.getComputerModel();

    loadPersonTable(personModel);
    loadCompTable(computerModel);

    showAdvSearchPersons = 0;
    ui->widget_moreFilterOpsPersons->setVisible(showAdvSearchPersons);
    ui->widget_moreFilterOpsPersons->setEnabled(showAdvSearchPersons);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadPersonTable(QSqlRelationalTableModel * model)
{
    ui->table_Person-> setModel(model);
    ui->table_Person->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->table_Person->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->table_Person->verticalHeader()->hide();
    ui->table_Person->setColumnHidden(0,true);
}

void MainWindow::loadCompTable(QSqlRelationalTableModel * model)
{
    ui->table_Comp-> setModel(model);
    ui->table_Comp->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->table_Comp->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->table_Comp->verticalHeader()->hide();
    ui->table_Comp->setColumnHidden(0,true);
}


void MainWindow::searchPerson()
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

        QString nationality = "" ;                                                  //TODO! Tengja við drop down!

        loadPersonTable(domain.searchPerson(searchInput, gender, BYfrom, BYto, DYfrom, DYto, nationality));
    }
    else
    {
        loadPersonTable(domain.searchPerson(searchInput));
    }
}


void MainWindow::searchComp(const QString& searchInput)
{
 /*   QString search = ui->searchInput_Comp->text();
    std::cout << search.toStdString();

    if(currentCompSearchIndex == 0)
    {
        loadCompTable(domain.searchComputerName(search));
    }
    else if(currentCompSearchIndex == 1)
    {
        loadCompTable(domain.searchComputerType(search));
    }
    else if(currentCompSearchIndex == 2)
    {
        loadCompTable(domain.searchComputerDY(search));
    }
    else if(currentCompSearchIndex == 3)
    {
        loadCompTable(domain.searchComputerBY(search));
    }
    */
}

void MainWindow::on_input_searchPerson_textEdited()
{
    searchPerson();
}

void MainWindow::on_searchInput_Comp_textEdited(const QString& searchString)
{
    searchComp(searchString);
}

void MainWindow::on_button_advSearchPerson_released()
{
    if(showAdvSearchPersons)
    {
        //todo: hreinsa advanced search
    }

    showAdvSearchPersons = !showAdvSearchPersons;
    ui->widget_moreFilterOpsPersons->setVisible(showAdvSearchPersons);
    ui->widget_moreFilterOpsPersons->setEnabled(showAdvSearchPersons);
}


void MainWindow::on_checkBox_searchFemale_released()
{
    ui->checkBox_searchMale->setChecked(false);
    searchPerson();
}

void MainWindow::on_checkBox_searchMale_released()
{
    ui->checkBox_searchFemale->setChecked(false);
    searchPerson();
}

void MainWindow::on_input_searchBornFrom_editingFinished()
{
    searchPerson();
}

void MainWindow::on_input_searchBornTo_editingFinished()
{
    searchPerson();
}

void MainWindow::on_input_searchDiedFrom_editingFinished()
{
    searchPerson();
}

void MainWindow::on_input_searchDiedTo_editingFinished()
{
    searchPerson();
}
