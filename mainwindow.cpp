#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "person.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
   // ui->tableWidget->setColumnHidden(0,1);
    ui->tableWidget->setSortingEnabled(1);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    loadPersonTable(domain.getPersonList());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPersonTable(vector<Person> pList){
    ui->tableWidget->setRowCount(pList.size());
    QMap<int,QMap<QString,QString>> genderList = domain.getAcceptedGender();

    for(size_t i = 0; i < pList.size();i++){
        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(QString::fromStdString(pList[i].getName() ));

        int gId = pList[i].getGender();
        QMap<QString,QString> g = genderList.value(gId);

        QTableWidgetItem *gender = new QTableWidgetItem;
        gender->setText(g.keys().at(0));
        gender->setData(Qt::DisplayRole, gId);

        QTableWidgetItem *nationality = new QTableWidgetItem;
        nationality->setText(QString::fromStdString(pList[i].getNationality() ));

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
}

void MainWindow::on_addEntry_clicked()
{
    QMap<int,QMap<QString,QString>> genderList = domain.getAcceptedGender();
    QMap<QString,int> gList;
    QMapIterator<int,QMap<QString,QString>> i(genderList);
    while (i.hasNext()) {
        i.next();
        gList.insert(i.value().values().at(0),i.key());
    }

    if(lastSelectedRow == utils.dummyNull){
        addEntryWindow = new AddEntry(this,gList);
        editEntry = utils.dummyNull;
    }else{
        editEntry = ui->tableWidget->item(lastSelectedRow,0)->text().toInt();
        addEntryWindow = new AddEntry(this,gList
                              ,ui->tableWidget->item(lastSelectedRow,1)->text()
                              ,ui->tableWidget->item(lastSelectedRow,2)->data(Qt::DisplayRole).toInt()
                              ,ui->tableWidget->item(lastSelectedRow,3)->text()
                              ,ui->tableWidget->item(lastSelectedRow,5)->text().toInt()
                              ,ui->tableWidget->item(lastSelectedRow,6)->text().toInt());
    }

    this->setEnabled(false);
    addEntryWindow->setEnabled(true);
    addEntryWindow->show();

    QObject::connect(addEntryWindow, SIGNAL(newEntryAccepted(const QString &, const int &, const QString &, const int &, const int &, const int &)), this,
                     SLOT(onNewEntryAccepted(const QString &, const int &, const QString &, const int &, const int &, const int &)));

    QObject::connect(addEntryWindow, SIGNAL(newEntryRejected()), this, SLOT(onNewEntryRejected()));
}

void MainWindow::onNewEntryRejected(){
    this->setEnabled(true);
}


void MainWindow::onNewEntryAccepted(const QString &n, const int &g, const QString &nat, const int &b, const int &d)
{
    this->setEnabled(true);
    /*
    // Adding a new item to the list widget
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(n));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem(nat));

    QTableWidgetItem *gender = new QTableWidgetItem;
    gender->setData(Qt::DisplayRole, g );
    ui->tableWidget->setItem(0,2, gender);

    QTableWidgetItem *age = new QTableWidgetItem;
    age->setData(Qt::DisplayRole, d == 0?QDate::currentDate().year()-b:d-b );
    ui->tableWidget->setItem(0,4, age);

    QTableWidgetItem *bY = new QTableWidgetItem;
    bY->setData(Qt::DisplayRole, b );
    ui->tableWidget->setItem(0,5, bY);

    QTableWidgetItem *dY = new QTableWidgetItem;
    dY->setData(Qt::DisplayRole, d );
    ui->tableWidget->setItem(0,6, dY);*/

    if(editEntry != utils.dummyNull){
        //todo edit
    }else{
        Person newPerson(n.toStdString(), g, b, d, nat.toStdString(), editEntry);
        domain.addPerson(newPerson);
    }

    loadPersonTable(domain.getPersonList());
}

void MainWindow::on_tableWidget_itemClicked()
{
    int row = ui->tableWidget->selectionModel()->currentIndex().row();
    if(lastSelectedRow == row){
        ui->tableWidget->selectionModel()->clearSelection();
        lastSelectedRow = utils.dummyNull;
        ui->addEntry->setText("Add");
    }else{
        lastSelectedRow = row;
        ui->addEntry->setText("Edit");
    }
    //int id = ui->tableWidget->item(row,0)->text().toInt();
}
