#include "gui.h"
#include "ui_gui.h"

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
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    personModel = domain.getPersonModel();
    computerModel = domain.getComputerModel();

    fillSearchComboBoxP();

    loadTopTable(personModel);

    connect(
      ui->tableView->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(onSelectionChange(const QItemSelection &, const QItemSelection &))
     );

    connect(ui->quickSearchInput, SIGNAL(returnPressed()),ui->searchButton,SLOT(click()));
}

Gui::~Gui()
{
    delete ui;
}

void Gui::checkStatus()
{

    int selected = ui->tableView->selectionModel()->selectedRows().size();

    if(selected)
    {
        ui->deleteButton->setEnabled(true);
        ui->addEditButton->setText("Edit");
        selected > 1 ? ui->addEditButton->setEnabled(false) : ui->addEditButton->setEnabled(true);
    }else
    {
        ui->deleteButton->setEnabled(false);
        ui->addEditButton->setText("Add");

    }

    bool hasChanged = 0;
    if(currentMode == Person)
    {
        hasChanged = personModel->isDirty();
    }
    else if(currentMode == Computer)
    {
        hasChanged = computerModel->isDirty();
    }

    if(hasChanged)
    {
        ui->saveButton->setEnabled(true);
        ui->revertButton->setEnabled(true);
    }
    else
    {
        ui->saveButton->setEnabled(false);
        ui->revertButton->setEnabled(false);
    }
}

void Gui::loadTopTable(QSqlRelationalTableModel * model)
{
    ui->tableView-> setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setColumnHidden(0,true);
}

void Gui::loadBottomTable(QSqlQueryModel * model){
    ui->tableView_2-> setModel(model);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->tableView_2->verticalHeader()->hide();
    ui->tableView_2->setColumnHidden(0,true);
}

void Gui::loadBottomTableEditMode(QSqlRelationalTableModel * model){
    ui->tableView_2-> setModel(model);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->tableView_2->verticalHeader()->hide();
    ui->tableView_2->setColumnHidden(0,true);
}



void Gui::on_addEditButton_clicked()
{
    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();

    if(currentMode == Person)
    {

        if(selectedList.size()) //if user has selection
        {
            onEditPersonButton();
        }else
        {
            onAddPersonButton();
        }

    }else if(currentMode == Computer)
    {

        if(selectedList.size()){ //if user has selection
            onEditComputerButton();
        }else
        {
            onAddComputerButton();
        }

    }
}

void Gui::onAddPersonButton()
{

    QMap<QString, int> gList = domain.getAcceptedGenderName();
    personDialogWindow = new PersonDialog(this,gList);

    QObject::connect(personDialogWindow, SIGNAL(personRejected()), this, SLOT(onPersonRejected()));
    QObject::connect(personDialogWindow,
                     SIGNAL(newPersonAccepted(const QString &, const int &, const QString &, const int &, const int &)),
                     this,
                     SLOT(onNewPersonAccepted(const QString &, const int &, const QString &, const int &, const int &)));

    this->setEnabled(false);
    personDialogWindow->setEnabled(true);
    personDialogWindow->show();

}

void Gui::onEditPersonButton()
{
    QMap<QString, int> gList = domain.getAcceptedGenderName();

    lastSelection = ui->tableView->selectionModel()->selectedRows().last().row();

    personDialogWindow = new PersonDialog(this,gList
                          ,ui->tableView->model()->index(lastSelection,1).data().toString()
                          ,ui->tableView->model()->index(lastSelection,2).data().toString()
                          ,ui->tableView->model()->index(lastSelection,3).data().toString()
                          ,ui->tableView->model()->index(lastSelection,4).data().toInt()
                          ,ui->tableView->model()->index(lastSelection,5).data().toInt()
                          ,ui->tableView->model()->index(lastSelection,0).data().toInt());

    QObject::connect(personDialogWindow, SIGNAL(personRejected()), this, SLOT(onPersonRejected()));
    QObject::connect(personDialogWindow,
                     SIGNAL(editPersonAccepted(const int &,const QString &, const int &, const QString &, const int &, const int &)),
                     this,
                     SLOT(onEditPersonAccepted(const int &,const QString &, const int &, const QString &, const int &, const int &)));

    this->setEnabled(false);
    personDialogWindow->setEnabled(true);
    personDialogWindow->show();
}

void Gui::onAddComputerButton()
{
    QMap<QString, int> tList = domain.getAcceptedComputerTypeName();
    computerDialogWindow = new ComputerDialog(this,tList);

    QObject::connect(computerDialogWindow, SIGNAL(computerRejected()), this, SLOT(onComputerRejected()));
    QObject::connect(computerDialogWindow,
                     SIGNAL(newComputerAccepted(const QString &, const int &, const int &, const int &)),
                     this,
                     SLOT(onComputerAccepted(const QString &, const int &, const int &, const int &)));

    this->setEnabled(false);
    computerDialogWindow->setEnabled(true);
    computerDialogWindow->show();

}

void Gui::onEditComputerButton()
{
    QMap<QString, int> tList = domain.getAcceptedComputerTypeName();

    lastSelection = ui->tableView->selectionModel()->selectedRows().last().row();

    computerDialogWindow = new ComputerDialog(this,tList
                          ,ui->tableView->model()->index(lastSelection,1).data().toString()
                          ,ui->tableView->model()->index(lastSelection,2).data().toString()
                          ,ui->tableView->model()->index(lastSelection,3).data().toInt()
                          ,ui->tableView->model()->index(lastSelection,4).data().toInt()
                          ,ui->tableView->model()->index(lastSelection,0).data().toInt());

    QObject::connect(computerDialogWindow, SIGNAL(computerRejected()), this, SLOT(onComputerRejected()));
    QObject::connect(computerDialogWindow,
                     SIGNAL(editComputerAccepted(const int &,const QString &, const int &, const int &, const int &)),
                     this,
                     SLOT(onEditComputerAccepted(const int &,const QString &, const int &, const int &, const int &)));

    this->setEnabled(false);
    computerDialogWindow->setEnabled(true);
    computerDialogWindow->show();
}

void Gui::onPersonRejected()
{
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

    checkStatus();
}

void Gui::onEditPersonAccepted(const int &id, const QString &n, const int &g, const QString &nat, const int &b, const int &d)
{

    lastSelection = ui->tableView->selectionModel()->selectedRows().last().row();

    this->setEnabled(true);
    QSqlRecord record = personModel->record();
    record.setValue(0,id);
    record.setValue(1,n);
    record.setValue(2,g);
    record.setValue(3,nat);
    record.setValue(4,b);
    record.setValue(5,d);
    personModel->setRecord(lastSelection,record);
    ui->tableView->setModel(personModel);

    checkStatus();
}

void Gui::onComputerAccepted(const QString &n, const int &t, const int &d, const int &b)
{

    this->setEnabled(true);

    QSqlRecord record = computerModel->record();
    record.setValue(1,n);
    record.setValue(2,t);
    record.setValue(3,d);
    record.setValue(4,b);
    computerModel->insertRecord(-1,record);
    ui->tableView->setModel(computerModel);

    checkStatus();

}

void Gui::onEditComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b)
{

    lastSelection = ui->tableView->selectionModel()->selectedRows().last().row();

    this->setEnabled(true);
    QSqlRecord record = computerModel->record();
    record.setValue(0,id);
    record.setValue(1,n);
    record.setValue(2,t);
    record.setValue(3,d);
    record.setValue(4,b);
    computerModel->setRecord(lastSelection,record);
    ui->tableView->setModel(computerModel);

    checkStatus();
}


void Gui::onComputerRejected()
{
    this->setEnabled(true);
}

void Gui::on_tableView_clicked(const QModelIndex &index)
{

    if(lastSelection == index.row() )
    {

        overrideOnSelectionChange = true;

        ui->tableView->selectionModel()->clearSelection();
        lastSelection = -1;

        overrideOnSelectionChange = false;

    }else
    {
        lastSelection = index.row();

        loadRelation();

    }

    checkStatus();

}

void Gui::onSelectionChange(const QItemSelection &a, const QItemSelection &b)
{
    if(!overrideOnSelectionChange)
    {
        lastSelection = -1;
    }

    checkStatus();
}

void Gui::loadRelation(){

    if(!editMode){
        QString id = ui->tableView->model()->index(lastSelection,0).data().toString();

        if(currentMode == Person)
        {
            std::cout << id.toStdString() << "\n";
            loadBottomTable(domain.getPersonRelationModel(id));
        }
        else if(currentMode == Computer)
        {
            QString id = ui->tableView->model()->index(lastSelection,0).data().toString();
            loadBottomTable(domain.getComputerRelationModel(id));
        }
    }
}

void Gui::on_saveButton_released()
{
    if(currentMode == Person)
    {
        saveModel(personModel);
    }
    else if(currentMode == Computer)
    {
        saveModel(computerModel);
    }

    for(int i = 0; i < ui->tableView->model()->rowCount(); i++)
    {
        ui->tableView->showRow(i);
    }

    checkStatus();
}

void Gui::saveModel(QSqlRelationalTableModel * model)
{
    domain.submitDatabaseChanges(model);
}

void Gui::on_deleteButton_released()
{
    QModelIndexList selList = ui->tableView->selectionModel()->selectedRows();

    if(currentMode == Person)
    {
        for(int i = 0; i < selList.size(); i++){
            ui->tableView->hideRow(selList[i].row());
            personModel->removeRow(selList[i].row());
        }
    }
    else if(currentMode == Computer)
    {
        for(int i = 0; i < selList.size(); i++){
            ui->tableView->hideRow(selList[i].row());
            computerModel->removeRow(selList[i].row());
        }
    }

    checkStatus();
}

void Gui::on_revertButton_released()
{
    if(currentMode == Person)
    {
        revertModel(personModel);
    }
    else if(currentMode == Computer)
    {
        revertModel(computerModel);
    }

    checkStatus();
}

void Gui::revertModel(QSqlRelationalTableModel * model)
{

    model->revertAll();

    for(int i = 0; i < model->rowCount(); i++)
    {
        ui->tableView->showRow(i);
    }

    ui->tableView->setModel(model);
}

void Gui::on_comboBox_currentIndexChanged(int index)
{

    if(index == 0) //person
    {

        switchToPerson();

    }else if(index == 1)  //computer
    {

        switchToComputer();
    }

    connect(
      ui->tableView->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(onSelectionChange(const QItemSelection &, const QItemSelection &))
     );

    checkStatus();
}

void Gui::switchToPerson() //happens on switch to person
{

    if(computerModel->isDirty())
    {
        QString promptTitle = "Save";
        QString promptQuestion = "Would you like to save Computer before changing?";
        QMessageBox::StandardButton prompt = QMessageBox::question(this,promptTitle, promptQuestion ,
                                                                   QMessageBox::Yes|QMessageBox::No);

        if (prompt == QMessageBox::Yes)
        {
            saveModel(computerModel);
        }
        else if(prompt == QMessageBox::No)
        {
            revertModel(computerModel);
        }
    }

    currentMode = Person;
    ui->tableView->selectionModel()->clearSelection();
    loadTopTable(domain.getPersonModel());

    fillSearchComboBoxP();
    //todo load bottom
}

void Gui::switchToComputer() //happens on switch to computer
{

    if(personModel->isDirty())
    {
        QString promptTitle = "Save";
        QString promptQuestion = "Would you like to save Computer before changing?";
        QMessageBox::StandardButton prompt = QMessageBox::question(this, promptTitle, promptQuestion ,
                                                                   QMessageBox::Yes|QMessageBox::No);

        if (prompt == QMessageBox::Yes)
        {
            saveModel(personModel);
        }
        else if(prompt == QMessageBox::No)
        {
            revertModel(personModel);
        }
    }

     currentMode = Computer;
     ui->tableView->selectionModel()->clearSelection();
     loadTopTable(domain.getComputerModel());

     fillSearchComboBoxC();
     //todo load bottom

}

void Gui::on_searchButton_released()
{
 /*   QString search = ui->quickSearchInput->text();
    std::cout << search.toStdString();

    if(currentMode == Person)
    {
        if(currentSearchIndex == 0)
        {
            loadTopTable(domain.searchPersonName(search));
        }
        else if(currentSearchIndex == 1)
        {
            loadTopTable(domain.searchPersonGender(search));
        }
        else if(currentSearchIndex == 2)
        {
            loadTopTable(domain.searchPersonNationality(search));
        }
        else if(currentSearchIndex == 3)
        {
            loadTopTable(domain.searchPersonBY(search));
        }
        else if(currentSearchIndex == 4)
        {
            loadTopTable(domain.searchPersonDY(search));
        }
    }
    else if(currentMode == Computer)
    {
        if(currentSearchIndex == 0)
        {
            loadTopTable(domain.searchComputerName(search));
        }
        else if(currentSearchIndex == 1)
        {
            loadTopTable(domain.searchComputerType(search));
        }
        else if(currentSearchIndex == 2)
        {
            loadTopTable(domain.searchComputerDY(search));
        }
        else if(currentSearchIndex == 3)
        {
            loadTopTable(domain.searchComputerBY(search));
        }
    }

  */
}

void Gui::fillSearchComboBoxP()
{
    ui->searchComboBox->clear();
    ui->searchComboBox->addItem("Name",0);
    ui->searchComboBox->addItem("Gender",1);
    ui->searchComboBox->addItem("Nationality",2);
    ui->searchComboBox->addItem("Birth year",3);
    ui->searchComboBox->addItem("Death year",4);

};

void Gui::fillSearchComboBoxC()
{
    ui->searchComboBox->clear();
    ui->searchComboBox->addItem("Name",0);
    ui->searchComboBox->addItem("Type",1);
    ui->searchComboBox->addItem("Design year",2);
    ui->searchComboBox->addItem("Build year",3);
};

void Gui::on_searchComboBox_currentIndexChanged(int index)
{
    currentSearchIndex = index;
}

void Gui::on_editRelation_toggled(bool checked)
{
    editMode = checked;
    if(editMode)
    {
        ui->addRelButton->setEnabled(true);

        if(currentMode == Computer){
            loadBottomTableEditMode(personModel);
        }else if(currentMode == Person){
            loadBottomTableEditMode(computerModel);
        }

    }else{
        ui->addRelButton->setEnabled(false);
        loadRelation();
    }
}

void Gui::on_addRelButton_released()
{
    //add relation

    int computerId, personId;
    QString computerName,  personName;

    if(currentMode == Computer)
    {
        computerId = ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),0).data().toInt();
        personId = ui->tableView_2->model()->index(ui->tableView_2->selectionModel()->currentIndex().row(),0).data().toInt();
        computerName = ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),1).data().toString();
        personName = ui->tableView_2->model()->index(ui->tableView_2->selectionModel()->currentIndex().row(),1).data().toString();
    }
    else if(currentMode == Person)
    {
        personId = ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),0).data().toInt();
        computerId = ui->tableView_2->model()->index(ui->tableView_2->selectionModel()->currentIndex().row(),0).data().toInt();
        computerName = ui->tableView_2->model()->index(ui->tableView_2->selectionModel()->currentIndex().row(),1).data().toString();
        personName = ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),1).data().toString();
    }

    QString promptTitle = "Create Relation";
    QString promptQuestion = "Create a relation between," + personName + " and "+computerName+".";
    promptQuestion.append("\nThis will save changes, are you sure?");
    QMessageBox::StandardButton prompt = QMessageBox::question(this,promptTitle, promptQuestion ,
                                                               QMessageBox::Yes|QMessageBox::No);

    if(prompt == QMessageBox::Yes)
    {
        domain.createPCRelation(personId, computerId);
    }

    if(currentMode == Computer)
    {
        loadBottomTable(domain.getComputerModel());
    }
    else if(currentMode == Person)
    {
        loadBottomTable(domain.getPersonModel());
    }

}

