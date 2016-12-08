#include "gui.h"
#include "ui_gui.h"
#include "person.h"
#include <string>
#include <iostream>
#include <QMessageBox>

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    loadTopTable(domain.getPersonModel());
}

Gui::~Gui()
{
    delete ui;
}

void Gui::loadTopTable(QSqlRelationalTableModel * model){
    personModel = model;
    //QMap<int,QMap<QString,QString>> genderList = domain.getAcceptedGender();
    ui->tableView-> setModel(personModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->tableView->setColumnHidden(0,true);
    /*
    for(size_t i = 0; i < pList.size();i++){
        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(pList[i].getName());

        int gId = pList[i].getGender();
        QMap<QString,QString> g = genderList.value(gId);

        QTableWidgetItem *gender = new QTableWidgetItem;
        gender->setText(g.keys().at(0));
        gender->setData(Qt::DisplayRole, gId);

        QTableWidgetItem *nationality = new QTableWidgetItem;
        nationality->setText(pList[i].getNationality());

        QTableWidgetItem *age = new QTableWidgetItem;
        age->setData(Qt::DisplayRole, pList[i].getAge() );

        QTableWidgetItem *bYear = new QTableWidgetItem;
        bYear->setData(Qt::DisplayRole, pList[i].getBirthYear());

        QTableWidgetItem *dYear = new QTableWidgetItem;
        dYear->setData(Qt::DisplayRole, pList[i].getDeathYear());

        QTableWidgetItem *id = new QTableWidgetItem;
        id->setData(Qt::DisplayRole, pList[i].getPersonId());

        ui->tableWidget->setItem(i,0,id);
        ui->tableWidget->setItem(i,1,name);
        ui->tableWidget->setItem(i,2,gender);
        ui->tableWidget->setItem(i,3,nationality);
        ui->tableWidget->setItem(i,4,age);
        ui->tableWidget->setItem(i,5,bYear);
        ui->tableWidget->setItem(i,6,dYear);
    }

    */
}


void Gui::on_personAddEdit_clicked()
{
    QMap<QString, int> gList = domain.getAcceptedGenderName();

    if(lastSelectedRow == utils.dummyNull){
        personDialogWindow = new PersonDialog(this,gList);

        QObject::connect(personDialogWindow, SIGNAL(newPersonAccepted(const QString &, const int &, const QString &, const int &, const int &)), this,
                         SLOT(onNewPersonAccepted(const QString &, const int &, const QString &, const int &, const int &)));

    }else{
        personDialogWindow = new PersonDialog(this,gList
                              ,ui->tableView->model()->index(lastSelectedRow,1).data().toString()
                              ,ui->tableView->model()->index(lastSelectedRow,2).data().toString()
                              ,ui->tableView->model()->index(lastSelectedRow,3).data().toString()
                              ,ui->tableView->model()->index(lastSelectedRow,4).data().toInt()
                              ,ui->tableView->model()->index(lastSelectedRow,5).data().toInt()
                              ,ui->tableView->model()->index(lastSelectedRow,0).data().toInt());

        QObject::connect(personDialogWindow, SIGNAL(editPersonAccepted(const int &,const QString &, const int &, const QString &, const int &, const int &)), this,
                         SLOT(onEditPersonAccepted(const int &,const QString &, const int &, const QString &, const int &, const int &)));
    }

    this->setEnabled(false);
    personDialogWindow->setEnabled(true);
    personDialogWindow->show();

    QObject::connect(personDialogWindow, SIGNAL(personEntryRejected()), this, SLOT(onPersonEntryRejected()));
}

void Gui::onPersonEntryRejected(){
    this->setEnabled(true);
}


void Gui::onNewPersonAccepted(const QString &n, const int &g, const QString &nat, const int &b, const int &d)
{
    this->setEnabled(true);

    QSqlRecord record = personModel->record();
    record.setValue(1,n);
    record.setValue(2,g);
    record.setValue(3,nat);
    record.setValue(4,b);
    record.setValue(5,d);
    personModel->insertRecord(-1,record);
    ui->tableView->setModel(personModel);
    //ui->tableView->setModel(domain.submitDatabaseChanges(personModel));

    //loadTable(domain.getPersonModel());
    //todo hasChange++
}

void Gui::onEditPersonAccepted(const int &id, const QString &n, const int &g, const QString &nat, const int &b, const int &d){

    this->setEnabled(true);
    QSqlRecord record = personModel->record();
    record.setValue(0,id);
    record.setValue(1,n);
    record.setValue(2,g);
    record.setValue(3,nat);
    record.setValue(4,b);
    record.setValue(5,d);
    personModel->setRecord(lastSelectedRow,record);
    ui->tableView->setModel(personModel);
    //todo hasChange++
};

void Gui::on_tableView_clicked(const QModelIndex &index)
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    if(lastSelectedRow == row){
        ui->tableView->selectionModel()->clearSelection();
        lastSelectedRow = utils.dummyNull;
        ui->personAddEdit->setText("Add");
    }else{
        lastSelectedRow = row;
        ui->personAddEdit->setText("Edit");
    }
    //int id = ui->tableWidget->item(row,0)->text().toInt();
}

void Gui::on_savePerson_clicked()
{
    domain.submitDatabaseChanges(personModel);
}

void Gui::on_deletePerson_released()
{
    //todo hasChange++

    ui->tableView->hideRow(lastSelectedRow);
    personModel->removeRow(lastSelectedRow);
    ui->tableView->setModel(personModel);
}

void Gui::on_peopleRevert_released()
{
    personModel->revertAll();

    for(int i = 0; i < personModel->rowCount(); i++){
        ui->tableView->showRow(i);
    }

    ui->tableView->setModel(personModel);
}

void Gui::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){
        std::cout << "1";

        QMessageBox mb("Save?","Would you like to save before changing?",
                               QMessageBox::Question,
                               QMessageBox::Yes | QMessageBox::Default,
                               QMessageBox::No  | QMessageBox::Escape,
                               QMessageBox::NoButton);
        if (mb.exec() == QMessageBox::Yes){
            //leaving computer table, save changes
            //domain.submitDatabaseChanges(computerModel);
        }

        loadTopTable(domain.getPersonModel());
    }else if(index == 1){
        std::cout << "2";

        //todo load computermodel
    }
}

<<<<<<< HEAD


void Gui::on_pushButton_released()
{
    QMap<int, QString> tList = domain.getAcceptedTypeStrings();
    computerDialogWindow = new computerDialog(this, tList);
    computerDialogWindow->show();   
=======
void Gui::on_search_released()
{
    searchPersonDialogWindow = new SearchPersonDialog(this);
    searchPersonDialogWindow->show();
>>>>>>> origin/master
}
