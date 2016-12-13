#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->personinfo->setVisible(false);
    ui->computerInfo->setVisible(false);

    personModel = domain.getPersonModel();
    computerModel = domain.getComputerModel();
    proxyPersonModel->setDynamicSortFilter(true);

    ui->table_Person->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_Comp->setSelectionBehavior(QAbstractItemView::SelectRows);

    loadPersonTable();
    loadCompTable();

    fillNationalitySearchBox(domain.getAcceptedNationality());

    showAdvSearchPersons = 0;
    ui->widget_moreFilterOpsPersons->setVisible(showAdvSearchPersons);

    connect(
      ui->table_Comp->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(onCompSelectionChange())
     );

    connect(
      ui->table_Person->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(onPersonSelectionChange())
     );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPersonTable()
{
    proxyPersonModel->setSourceModel(personModel);
    ui->table_Person->setModel(proxyPersonModel);
    ui->table_Person->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->table_Person->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->table_Person->verticalHeader()->hide();
    ui->table_Person->setColumnHidden(0,true);

    connect(ui->table_Person,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(personRightClick(QPoint)));
}

void MainWindow::loadCompTable()
{
    proxyCompModel->setSourceModel(computerModel);
    ui->table_Comp-> setModel(proxyCompModel);
    ui->table_Comp->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->table_Comp->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->table_Comp->verticalHeader()->hide();
    ui->table_Comp->setColumnHidden(0,true);

    connect(ui->table_Comp,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(computerRightClick(QPoint)));
}


void MainWindow::fillNationalitySearchBox(QMap<QString,int> natList){

    ui->input_searchNat->addItem("",0);
    QMapIterator<QString, int> i(natList);
    while (i.hasNext())
    {
        i.next();
        ui->input_searchNat->addItem(i.key(),i.value());
    }

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
        QString nationality = ui->input_searchNat->itemData(ui->input_searchNat->currentIndex()).toString();

        personModel = domain.searchPerson(searchInput, gender, BYfrom, BYto, DYfrom, DYto, nationality);
    }
    else
    {
        personModel = domain.searchPerson(searchInput);
    }
    loadPersonTable();
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
        ui->input_searchNat->setCurrentIndex(0);
    }

    showAdvSearchPersons = !showAdvSearchPersons;
    ui->widget_moreFilterOpsPersons->setVisible(showAdvSearchPersons);
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

void MainWindow::on_input_searchNat_currentIndexChanged(const QString &nat)
{
    searchPerson();
}

void MainWindow::on_table_Person_clicked(const QModelIndex &index)
{

    if(lastPersonSelection == index.row())
    {
        overrideOnPersonSelectionChange = true;

        ui->table_Person->selectionModel()->clearSelection();
        lastPersonSelection = -1;
        ui->personinfo->setVisible(false);

        overrideOnPersonSelectionChange = false;

    }else
    {
        lastPersonSelection = index.row();

        //loadRelation();
    }

    //checkStatus();

}

void MainWindow::onPersonSelectionChange()
{
    if(!overrideOnPersonSelectionChange && !ui->table_Person->selectionModel()->selectedRows().isEmpty())
    {
        lastPersonSelection = -1;
        ui->personinfo->show();
        ui->computerInfo->hide();
    }

    //checkStatus();
}


void MainWindow::on_table_Comp_clicked(const QModelIndex &index)
{

    if(lastCompSelection == index.row() )
    {
        overrideOnCompSelectionChange = true;

        ui->table_Comp->selectionModel()->clearSelection();
        lastCompSelection = -1;
        ui->computerInfo->setVisible(false);

        overrideOnCompSelectionChange = false;

    }else
    {
        lastCompSelection = index.row();

        //loadRelation();
    }

    //checkStatus();

}

void MainWindow::onCompSelectionChange()
{
    if(!overrideOnCompSelectionChange && !ui->table_Comp->selectionModel()->selectedRows().isEmpty())
    {
        lastCompSelection = 1;
        ui->computerInfo->show();
        ui->personinfo->hide();
    }

    //checkStatus();
}


void MainWindow::on_actionAdd_new_person_triggered()
{
    addPersonDialog();
}

void MainWindow::on_actionAdd_new_computer_triggered()
{
    addComputerDialog();
}

void MainWindow::on_actionEdit_person_triggered()
{
    editPersonDialog();
}

void MainWindow::on_actionEdit_Computer_triggered()
{
    editComputerDialog();
}


void MainWindow::addPersonDialog(){
    QMap<QString, int> gList = domain.getAcceptedGenderName();
    QMap<QString, int> natList = domain.getAcceptedNationality();
    personDialogWindow = new PersonDialog(this,gList, natList);

    QObject::connect(personDialogWindow, SIGNAL(personRejected()), this, SLOT(onPersonRejected()));
    QObject::connect(personDialogWindow,
                     SIGNAL(addPersonAccepted(const QString &, const int &, const int &, const int &, const int &)),
                     this,
                     SLOT(onAddPersonAccepted(const QString &, const int &, const int &, const int &, const int &)));

    this->setEnabled(false);
    personDialogWindow->setEnabled(true);
    personDialogWindow->show();
}

void MainWindow::addComputerDialog()
{
    QMap<QString, int> tList = domain.getAcceptedComputerTypeName();
    computerDialogWindow = new ComputerDialog(this,tList);

    QObject::connect(computerDialogWindow, SIGNAL(computerRejected()), this, SLOT(onComputerRejected()));
    QObject::connect(computerDialogWindow,
                     SIGNAL(addComputerAccepted(const QString &, const int &, const int &, const int &)),
                     this,
                     SLOT(onAddComputerAccepted(const QString &, const int &, const int &, const int &)));

    this->setEnabled(false);
    computerDialogWindow->setEnabled(true);
    computerDialogWindow->show();
}

void MainWindow::editPersonDialog()
{
    QMap<QString, int> gList = domain.getAcceptedGenderName();
    QMap<QString, int> natList = domain.getAcceptedNationality();

    personDialogWindow = new PersonDialog(this,gList,natList
                          ,ui->table_Person->model()->index(lastPersonSelection,1).data().toString()
                          ,ui->table_Person->model()->index(lastPersonSelection,2).data().toString()
                          ,ui->table_Person->model()->index(lastPersonSelection,3).data().toString()
                          ,ui->table_Person->model()->index(lastPersonSelection,4).data().toInt()
                          ,ui->table_Person->model()->index(lastPersonSelection,5).data().toInt()
                          ,ui->table_Person->model()->index(lastPersonSelection,0).data().toInt());

    QObject::connect(personDialogWindow, SIGNAL(personRejected()), this, SLOT(onPersonRejected()));
    QObject::connect(personDialogWindow,
                     SIGNAL(editPersonAccepted(const int &,const QString &, const int &, const int &, const int &, const int &)),
                     this,
                     SLOT(onEditPersonAccepted(const int &,const QString &, const int &, const int &, const int &, const int &)));

    this->setEnabled(false);
    personDialogWindow->setEnabled(true);
    personDialogWindow->show();
}

void MainWindow::editComputerDialog()
{
    QMap<QString, int> tList = domain.getAcceptedComputerTypeName();

    computerDialogWindow = new ComputerDialog(this,tList
                          ,ui->table_Comp->model()->index(lastCompSelection,1).data().toString()
                          ,ui->table_Comp->model()->index(lastCompSelection,2).data().toString()
                          ,ui->table_Comp->model()->index(lastCompSelection,3).data().toInt()
                          ,ui->table_Comp->model()->index(lastCompSelection,4).data().toInt()
                          ,ui->table_Comp->model()->index(lastCompSelection,0).data().toInt());

    QObject::connect(computerDialogWindow, SIGNAL(computerRejected()), this, SLOT(onComputerRejected()));
    QObject::connect(computerDialogWindow,
                     SIGNAL(editComputerAccepted(const int &,const QString &, const int &, const int &, const int &)),
                     this,
                     SLOT(onEditComputerAccepted(const int &,const QString &, const int &, const int &, const int &)));

    this->setEnabled(false);
    computerDialogWindow->setEnabled(true);
    computerDialogWindow->show();
}


void MainWindow::onPersonRejected()
{
    this->setEnabled(true);
}

void MainWindow::onComputerRejected()
{
    this->setEnabled(true);
}

void MainWindow::onAddPersonAccepted(const QString &n, const int &g, const int &nat, const int &b, const int &d)
{
    this->setEnabled(true);

    QSqlRecord record = personModel->record();
    record.setValue(1,n);
    record.setValue(2,g);
    record.setValue(3,nat);
    record.setValue(4,b);
    record.setValue(5,d);
    personModel->insertRecord(-1,record);
}

void MainWindow::onAddComputerAccepted(const QString &n, const int &t, const int &d, const int &b)
{
    this->setEnabled(true);

    QSqlRecord record = computerModel->record();
    record.setValue(1,n);
    record.setValue(2,t);
    record.setValue(3,d);
    record.setValue(4,b);
    computerModel->insertRecord(-1,record);
}

void MainWindow::onEditPersonAccepted(const int &id, const QString &n, const int &g, const int &nat, const int &b, const int &d)
{
    this->setEnabled(true);
    personModel->setData(personModel->index(lastPersonSelection,0),id);
    personModel->setData(personModel->index(lastPersonSelection,1),n);
    personModel->setData(personModel->index(lastPersonSelection,2),g);
    personModel->setData(personModel->index(lastPersonSelection,3),nat);
    personModel->setData(personModel->index(lastPersonSelection,4),b);
    personModel->setData(personModel->index(lastPersonSelection,5),d);

}

void MainWindow::onEditComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b)
{
    this->setEnabled(true);
    computerModel->setData(computerModel->index(lastCompSelection,0),id);
    computerModel->setData(computerModel->index(lastCompSelection,1),n);
    computerModel->setData(computerModel->index(lastCompSelection,2),t);
    computerModel->setData(computerModel->index(lastCompSelection,3),d);
    computerModel->setData(computerModel->index(lastCompSelection,4),b);
}

void MainWindow::on_actionSave_Changes_triggered()
{
    saveChanges();
}

void MainWindow::saveChanges(){

    if(personModel->isDirty()){
        saveModel(personModel);
    }

    if(computerModel->isDirty()){
        saveModel(computerModel);
    }

}

void MainWindow::saveModel(QSqlRelationalTableModel * model)
{
    domain.submitDatabaseChanges(model);
}

void MainWindow::personRightClick(QPoint position)
{
    QMenu *pContextMenu = new QMenu( this);
    pContextMenu->addAction(ui->menuEdit->actions().at(0));
    pContextMenu->addAction(ui->menuEdit->actions().at(2));
    pContextMenu->exec(QCursor::pos());
}

void MainWindow::computerRightClick(QPoint position)
{
    QMenu *cContextMenu = new QMenu( this);
    cContextMenu->addAction(ui->menuEdit->actions().at(1));
    cContextMenu->addAction(ui->menuEdit->actions().at(2));
    cContextMenu->exec(QCursor::pos());
}

void MainWindow::deleteSelected(){

    int index = ui->tabsWidget_personComputer->currentIndex();

    if(index == 0)//person
    {
        QModelIndexList selList = ui->table_Person->selectionModel()->selectedRows();
        for(int i = 0; i < selList.size(); i++){
            ui->table_Person->hideRow(selList[i].row());
            personModel->removeRow(selList[i].row());
        }
    }
    else if(index == 1)//computer
    {
        QModelIndexList selList = ui->table_Comp->selectionModel()->selectedRows();
        for(int i = 0; i < selList.size(); i++){
            ui->table_Comp->hideRow(selList[i].row());
            computerModel->removeRow(selList[i].row());
        }
    }
}

void MainWindow::on_actionDelete_triggered()
{
    deleteSelected();
}

void MainWindow::loadPersonInfo () {

    ui->label_name_pi->setText(ui->table_Person->model()->index(lastPersonSelection,1).data().toString());
    ui->label_nation_pi->setText(ui->table_Person->model()->index(lastPersonSelection,3).data().toString());
    ui->label_born_pi->setText(ui->table_Person->model()->index(lastPersonSelection,4).data().toString());
    ui->label_deathage_pi->setText(ui->table_Person->model()->index(lastPersonSelection,5).data().toString());

}

void MainWindow::loadComputerInfo() {

    ui->label_name_pi->setText(ui->table_Comp->model()->index(lastCompSelection,1).data().toString());
    ui->label_type_ci->setText(ui->table_Comp->model()->index(lastCompSelection,2).data().toString());
    ui->label_dy_ci->setText(ui->table_Comp->model()->index(lastCompSelection,3).data().toString());
    ui->label_by_ci->setText(ui->table_Comp->model()->index(lastCompSelection,4).data().toString() );

}
