#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fillSearchComboBoxP();
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


void MainWindow::fillSearchComboBoxP()
{
    ui->comboBox_searchPerson->addItem("Name",0);
    ui->comboBox_searchPerson->addItem("Gender",1);
    ui->comboBox_searchPerson->addItem("Nationality",2);
    ui->comboBox_searchPerson->addItem("Birth year",3);
    ui->comboBox_searchPerson->addItem("Death year",4);

};

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

void MainWindow::on_searchButton_Comp_released()
{
    QString search = ui->searchInput_Comp->text();
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
}

void MainWindow::on_searchButton_Person_released()
{
    QString search = ui->searchInput_Person->text();
    std::cout << search.toStdString();

    if(currentPersonSearchIndex == 0)
    {
        loadPersonTable(domain.searchPersonName(search));
    }
    else if(currentPersonSearchIndex == 1)
    {
        loadPersonTable(domain.searchPersonGender(search));
    }
    else if(currentPersonSearchIndex == 2)
    {
        loadPersonTable(domain.searchPersonNationality(search));
    }
    else if(currentPersonSearchIndex == 3)
    {
        loadPersonTable(domain.searchPersonBY(search));
    }
    else if(currentPersonSearchIndex == 4)
    {
        loadPersonTable(domain.searchPersonDY(search));
    }
}
