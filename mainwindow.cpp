#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fillSearchComboBoxC();

    personModel = domain.getPersonModel();
    computerModel = domain.getComputerModel();

    loadPersonTable(personModel);
    loadCompTable(computerModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::fillSearchComboBoxC()
{
    ui->comboBox_searchComputer->addItem("Name",0);
    ui->comboBox_searchComputer->addItem("Type",1);
    ui->comboBox_searchComputer->addItem("Design year",2);
    ui->comboBox_searchComputer->addItem("Build year",3);
};

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

void MainWindow::on_comboBox_searchPerson_currentIndexChanged(int index)
{
    currentPersonSearchIndex = index;
}

void MainWindow::on_comboBox_searchComputer_currentIndexChanged(int index)
{
    currentCompSearchIndex = index;
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

void MainWindow::searchPerson(const QString& searchInput)
{
    std::cout << searchInput.toStdString();

    if(currentPersonSearchIndex == 0)
    {
        loadPersonTable(domain.searchPersonName(searchInput));
    }
    else if(currentPersonSearchIndex == 1)
    {
        loadPersonTable(domain.searchPersonGender(searchInput));
    }
    else if(currentPersonSearchIndex == 2)
    {
        loadPersonTable(domain.searchPersonNationality(searchInput));
    }
    else if(currentPersonSearchIndex == 3)
    {
        loadPersonTable(domain.searchPersonBY(searchInput));
    }
    else if(currentPersonSearchIndex == 4)
    {
        loadPersonTable(domain.searchPersonDY(searchInput));
    }
}

void MainWindow::on_searchInput_Person_textEdited(const QString& searchString)
{
    searchPerson(searchString);
}

void MainWindow::on_searchInput_Comp_textEdited(const QString& searchString)
{
    searchComp(searchString);
}

void MainWindow::on_button_advSearchPerson_released()
{
    showMoreFilterOpsPersons = !showMoreFilterOpsPersons;
    ui->widget_moreFilterOpsPersons->setVisible(showMoreFilterOpsPersons);
    ui->widget_moreFilterOpsPersons->setEnabled(showMoreFilterOpsPersons);
}
