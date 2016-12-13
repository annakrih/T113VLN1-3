#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
}

void MainWindow::loadCompTable()
{
    proxyCompModel->setSourceModel(computerModel);
    ui->table_Comp-> setModel(proxyCompModel);
    ui->table_Comp->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->table_Comp->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->table_Comp->verticalHeader()->hide();
    ui->table_Comp->setColumnHidden(0,true);
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
      //  QString nationality = ui->input_searchNat->currentText();

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

    if(lastPersonSelection == index.row() )
    {
        overrideOnPersonSelectionChange = true;

        ui->table_Person->selectionModel()->clearSelection();
        lastPersonSelection = -1;

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
    if(!overrideOnPersonSelectionChange)
    {
        lastPersonSelection = -1;
    }else if(!ui->table_Person->selectionModel()->selectedRows().isEmpty()){
        lastPersonSelection = ui->table_Person->selectionModel()->selectedRows().last().row();
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
    if(!overrideOnCompSelectionChange)
    {
        lastCompSelection = -1;
    }else if(!ui->table_Comp->selectionModel()->selectedRows().isEmpty()){
        lastCompSelection = ui->table_Comp->selectionModel()->selectedRows().last().row();
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

<<<<<<< HEAD
void MainWindow::onEditComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b)
{
    this->setEnabled(true);
    computerModel->setData(computerModel->index(lastCompSelection,0),id);
    computerModel->setData(computerModel->index(lastCompSelection,1),n);
    computerModel->setData(computerModel->index(lastCompSelection,2),t);
    computerModel->setData(computerModel->index(lastCompSelection,3),d);
    computerModel->setData(computerModel->index(lastCompSelection,4),b);
}
=======
>>>>>>> origin/master
