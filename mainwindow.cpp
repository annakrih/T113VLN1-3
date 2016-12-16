#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet(domain.getCssString());
    ui->input_searchBornFrom->setValidator(new QIntValidator);
    ui->input_searchBornTo->setValidator(new QIntValidator);
    ui->input_searchDiedFrom->setValidator(new QIntValidator);
    ui->input_searchDiedTo->setValidator(new QIntValidator);
    ui->input_searchBuildYearFrom->setValidator(new QIntValidator);
    ui->input_searchBuildYearTo->setValidator(new QIntValidator);
    ui->input_searchDesignYearFrom->setValidator(new QIntValidator);
    ui->input_searchDesignYearTo->setValidator(new QIntValidator);

    ui->personInfoWidget->setVisible(false);
    ui->computerInfo->setVisible(false);

    nextPersonId = domain.getNextAutoId("Person");
    nextComputerId = domain.getNextAutoId("Computer");

    personModel = domain.getPersonModel();
    computerModel = domain.getComputerModel();
    relationModel = domain.getPCRelationModel();

    ui->pushButton_editSelectedEntry->setEnabled(false);
    ui->actionEdit_Computer->setEnabled(false);
    ui->actionEdit_person->setEnabled(false);
    ui->pushButton_Delete->setEnabled(false);
    ui->actionDelete->setEnabled(false);
    ui->pushButton_Revert->setEnabled(false);

    loadPersonTable();
    loadCompTable();

    fillNationalitySearchBox(domain.getAcceptedNationality());
    fillComputerTypeSearchBox(domain.getAcceptedComputerTypeName());

    showAdvSearchPersons = 0;
    ui->widget_advancedSearchPerson->setVisible(showAdvSearchPersons);

    showAdvSearchComps = 0;
    ui->widget_advancedSearchComp->setVisible(showAdvSearchComps);

    connect(
      ui->table_Person->selectionModel(),
      SIGNAL(currentRowChanged(const QModelIndex&,const QModelIndex&)),
      SLOT(onPersonSelectionChange(const QModelIndex&,const QModelIndex&))
     );

    connect(
      ui->table_Comp->selectionModel(),
      SIGNAL(currentRowChanged(const QModelIndex&,const QModelIndex&)),
      SLOT(onCompSelectionChange(const QModelIndex&,const QModelIndex&))
     );

    connect(ui->table_Person,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(personRightClick()));
    connect(ui->table_Comp,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(computerRightClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPersonTable()
{
    QList<int> list;
    list.append(2);
    list.append(3);
    proxyPersonModel->setRelationColumn(list);
    proxyPersonModel->setSourceModel(personModel);
    ui->table_Person->setModel(proxyPersonModel);
    ui->table_Person->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->table_Person->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->table_Person->verticalHeader()->hide();
    ui->table_Person->setColumnHidden(0,true);
    ui->table_Person->setColumnHidden(6,true);
    proxyPersonModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    ui->table_Person->setSelectionBehavior(QAbstractItemView::SelectRows);
    proxyPersonModel->setDynamicSortFilter(true);
    proxyPersonModel->sort(1, Qt::AscendingOrder);

}

void MainWindow::loadCompTable()
{
    QList<int> list;
    list.append(2);
    proxyPersonModel->setRelationColumn(list);
    proxyCompModel->setSourceModel(computerModel);
    ui->table_Comp-> setModel(proxyCompModel);
    ui->table_Comp->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->table_Comp->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->table_Comp->verticalHeader()->hide();
    ui->table_Comp->setColumnHidden(0,true);
    proxyCompModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    ui->table_Comp->setSelectionBehavior(QAbstractItemView::SelectRows);
    proxyCompModel->setDynamicSortFilter(true);
    proxyCompModel->sort(1, Qt::AscendingOrder);
}

void MainWindow::loadPITable()
{
    proxyPIModel->setSourceModel(computerModel);
    ui->tablePI->setModel(proxyPIModel);
    ui->tablePI->verticalHeader()->hide();
    ui->tablePI->setColumnHidden(0,true);
    proxyPIModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    ui->tablePI->setSelectionBehavior(QAbstractItemView::SelectRows);
    proxyPIModel->setDynamicSortFilter(true);


}

void MainWindow::loadCITable()
{
    proxyCIModel->setSourceModel(personModel);
    ui->tableCI-> setModel(proxyCIModel);
    ui->tableCI->verticalHeader()->hide();
    ui->tableCI->setColumnHidden(0,true);
    ui->tableCI->setColumnHidden(6,true);
    proxyCIModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    ui->tableCI->setSelectionBehavior(QAbstractItemView::SelectRows);
    proxyCIModel->setDynamicSortFilter(true);

}

void MainWindow::fillNationalitySearchBox(QMap<QString,int> natList)
{

    ui->input_searchNat->addItem("",0);
    QMapIterator<QString, int> i(natList);
    while (i.hasNext())
    {
        i.next();
        ui->input_searchNat->addItem(i.key(),i.value());
    }

}

void MainWindow::fillComputerTypeSearchBox(QMap<QString,int> compTypeList)
{
    ui->input_searchCompType->addItem("",0);
    QMapIterator<QString,int> i(compTypeList);
    while(i.hasNext())
    {
        i.next();
        ui->input_searchCompType->addItem(i.key(), i.value());
    }
}

void MainWindow::searchPersonModel()
{
    QList<int> lst;
    lst.append(1);
    QString name = ui->input_searchPerson->text();
    QString gender = "";
    QString nationality = "";
    QString BYfrom = "";
    QString DYfrom = "";

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
        QString BYto = ui->input_searchBornTo->text();
        lst.append(5);
        DYfrom = ui->input_searchDiedFrom->text();
        QString DYto = ui->input_searchDiedTo->text();
    }

    proxyPersonModel->setFilterKeyColumns(lst);
    proxyPersonModel->addFilterFixedString(1, name);
    if(showAdvSearchPersons){
        proxyPersonModel->addFilterFixedString(2, gender);
        proxyPersonModel->addFilterFixedString(3, nationality);
        proxyPersonModel->addFilterFixedString(4, BYfrom);
        proxyPersonModel->addFilterFixedString(5, DYfrom);
    }
    proxyPersonModel->invalidate();

    ui->table_Person->hideColumn(0);
    ui->table_Person->hideColumn(6);
}

void MainWindow::on_input_searchPerson_textEdited()
{
    searchPersonModel();
}

void MainWindow::on_button_advSearchComp_released()
{

    if(showAdvSearchComps)
    {
        ui->input_searchCompType->setCurrentIndex(0);
        ui->input_searchDesignYearFrom->clear();
        ui->input_searchDesignYearTo->clear();
        ui->input_searchBuildYearFrom->clear();
        ui->input_searchBuildYearTo->clear();
    }
    showAdvSearchComps = !showAdvSearchComps;
    ui->widget_advancedSearchComp->setVisible(showAdvSearchComps);
}

void MainWindow::searchCompModel()
{
    QList<int> lst;
    lst.append(1);
    QString name = ui->searchInput_Comp->text();
    QString DYfrom = "";
    QString DYto = "";
    QString BYfrom = "";
    QString BYto = "";
    QString compType = "";

    if(showAdvSearchComps)
    {
        lst.append(2);
        compType = ui->input_searchCompType->currentText();
        lst.append(3);
        DYfrom = ui->input_searchDesignYearFrom->text();
        DYto = ui->input_searchDesignYearTo->text();
        lst.append(4);
        BYfrom = ui->input_searchBuildYearFrom->text();
        BYto = ui->input_searchBuildYearTo->text();
    }

    proxyCompModel->setFilterKeyColumns(lst);
    proxyCompModel->addFilterFixedString(1, name);
    if(showAdvSearchComps){
        proxyCompModel->addFilterFixedString(2, compType);
        proxyCompModel->addFilterFixedString(3, DYfrom);
        proxyCompModel->addFilterFixedString(4, BYfrom);
    }
    proxyCompModel->invalidate();

    ui->table_Comp->hideColumn(0);
}


void MainWindow::on_searchInput_Comp_textEdited()
{
    searchCompModel();
}

void MainWindow::on_input_searchDesignYearFrom_editingFinished()
{
    searchCompModel();
}

void MainWindow::on_input_searchDesignYearTo_editingFinished()
{

}

void MainWindow::on_input_searchBuildYearFrom_editingFinished()
{
    searchCompModel();
}

void MainWindow::on_input_searchBuildYearTo_editingFinished()
{
    searchCompModel();
}

void MainWindow::on_button_advSearchPerson_released()
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
}


void MainWindow::on_checkBox_searchFemale_released()
{
    ui->checkBox_searchMale->setChecked(false);
    searchPersonModel();
}

void MainWindow::on_checkBox_searchMale_released()
{
    ui->checkBox_searchFemale->setChecked(false);
    searchPersonModel();
}

void MainWindow::on_input_searchBornFrom_editingFinished()
{
    searchPersonModel();
}

void MainWindow::on_input_searchBornTo_editingFinished()
{
    searchPersonModel();
}

void MainWindow::on_input_searchCompType_currentIndexChanged(const QString &arg1)
{
    searchCompModel();
}


void MainWindow::on_input_searchDiedFrom_editingFinished()
{
    searchPersonModel();
}

void MainWindow::on_input_searchDiedTo_editingFinished()
{
    searchPersonModel();
}

void MainWindow::on_input_searchNat_currentIndexChanged(const QString &arg1)
{
    searchPersonModel();
}

void MainWindow::on_table_Person_clicked(const QModelIndex &index)
{
    buttonEnabledFunct();

    if(lastPersonSelection == index.row() && !overrideTableClick)
    {
        overrideOnPersonSelectionChange = true;
        ui->table_Person->selectionModel()->clearSelection();
        lastPersonSelection = -1;
        ui->personInfoWidget->setVisible(false);
        overrideOnPersonSelectionChange = false;

        buttonEnabledFunct();
    }
    else if(!overrideTableClick)
    {
        int index = ui->table_Person->currentIndex().row();
        lastPersonSelection = index;
        loadPersonInfo();
    }



    overrideTableClick = false;
}

void MainWindow::onPersonSelectionChange(const QModelIndex &c,const QModelIndex &p)
{    
    if(!overrideOnPersonSelectionChange)
    {
        overrideTableClick = true;
        int index = c.row();
        lastPersonSelection = index;
        loadPersonInfo();

        buttonEnabledFunct();
    }
}


void MainWindow::on_table_Comp_clicked(const QModelIndex &index)
{
    buttonEnabledFunct();

    if(lastCompSelection == index.row() && !overrideTableClick)
    {
        overrideOnCompSelectionChange = true;
        ui->table_Comp->selectionModel()->clearSelection();
        lastCompSelection = -1;
        ui->computerInfo->setVisible(false);
        overrideOnCompSelectionChange = false;

        buttonEnabledFunct();
    }
    else if(!overrideTableClick)
    {
        int index = ui->table_Comp->currentIndex().row();
        lastCompSelection = index;
        loadComputerInfo();
    }
    overrideTableClick = false;

}

void MainWindow::onCompSelectionChange(const QModelIndex &c,const QModelIndex &p)
{
    if(!overrideOnCompSelectionChange)
    {
        overrideTableClick = true;
        int index = c.row();
        lastCompSelection = index;
        loadComputerInfo();

        buttonEnabledFunct();
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


void MainWindow::addPersonDialog()
{
    QMap<QString, int> gList = domain.getAcceptedGenderName();
    QMap<QString, int> natList = domain.getAcceptedNationality();
    personDialogWindow = new PersonDialog(this,gList, natList);

    QObject::connect(personDialogWindow, SIGNAL(personRejected()), this, SLOT(onDialogRejected()));
    QObject::connect(personDialogWindow,
                     SIGNAL(addPersonAccepted(const QString &, const int &, const int &, const int &, const int &, const QString &)),
                     this,
                     SLOT(onAddPersonAccepted(const QString &, const int &, const int &, const int &, const int &, const QString &)));

    this->setEnabled(false);
    personDialogWindow->setEnabled(true);
    personDialogWindow->show();
    changesMade = 1;
}

void MainWindow::addComputerDialog()
{
    QMap<QString, int> tList = domain.getAcceptedComputerTypeName();
    computerDialogWindow = new ComputerDialog(this,tList);

    QObject::connect(computerDialogWindow, SIGNAL(computerRejected()), this, SLOT(onDialogRejected()));
    QObject::connect(computerDialogWindow,
                     SIGNAL(addComputerAccepted(const QString &, const int &, const int &, const int &)),
                     this,
                     SLOT(onAddComputerAccepted(const QString &, const int &, const int &, const int &)));

    this->setEnabled(false);
    computerDialogWindow->setEnabled(true);
    computerDialogWindow->show();
    changesMade = 1;
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

    QObject::connect(personDialogWindow, SIGNAL(personRejected()), this, SLOT(onDialogRejected()));
    QObject::connect(personDialogWindow,
                     SIGNAL(editPersonAccepted(const int &,const QString &, const int &, const int &, const int &, const int &, const QString &)),
                     this,
                     SLOT(onEditPersonAccepted(const int &,const QString &, const int &, const int &, const int &, const int &, const QString &)));

    this->setEnabled(false);
    personDialogWindow->setEnabled(true);
    personDialogWindow->show();
    changesMade = 1;
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

    QObject::connect(computerDialogWindow, SIGNAL(computerRejected()), this, SLOT(onDialogRejected()));
    QObject::connect(computerDialogWindow,
                     SIGNAL(editComputerAccepted(const int &,const QString &, const int &, const int &, const int &)),
                     this,
                     SLOT(onEditComputerAccepted(const int &,const QString &, const int &, const int &, const int &)));

    this->setEnabled(false);
    computerDialogWindow->setEnabled(true);
    computerDialogWindow->show();
    changesMade = 1;
}


void MainWindow::onDialogRejected()
{
    this->setEnabled(true);
}


void MainWindow::onAddPersonAccepted(const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &imagePlace)
{
    this->setEnabled(true);

    QFile* file = new QFile(imagePlace);
    file->open(QIODevice::ReadOnly);
    QByteArray image = file->readAll();
    QString imageBlob = QString(image.toBase64());

    QSqlRecord record = personModel->record();
    record.setValue(0,nextPersonId);
    record.setValue(1,n);
    record.setValue(2,g);
    record.setValue(3,nat);
    record.setValue(4,b);
    record.setValue(5,d);
    record.setValue(6,imageBlob);
    personModel->insertRecord(-1,record);

    nextPersonId++;

    ui->tabsWidget_personComputer->setCurrentIndex(0);
    buttonEnabledFunct();
}

void MainWindow::onAddComputerAccepted(const QString &n, const int &t, const int &d, const int &b)
{
    this->setEnabled(true);

    QSqlRecord record = computerModel->record();
    record.setValue(0,nextComputerId);
    record.setValue(1,n);
    record.setValue(2,t);
    record.setValue(3,d);
    record.setValue(4,b);
    computerModel->insertRecord(-1,record);

    nextComputerId++;

    ui->tabsWidget_personComputer->setCurrentIndex(1);
    buttonEnabledFunct();
}

void MainWindow::onEditPersonAccepted(const int &id, const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &imagePlace)
{
    this->setEnabled(true);

    QFile* file = new QFile(imagePlace);
    file->open(QIODevice::ReadOnly);
    QByteArray image = file->readAll();
    QString imageBlob = QString(image.toBase64());

    personModel->setData(personModel->index(lastPersonSelection,0),id);
    personModel->setData(personModel->index(lastPersonSelection,1),n);
    personModel->setData(personModel->index(lastPersonSelection,2),g);
    personModel->setData(personModel->index(lastPersonSelection,3),nat);
    personModel->setData(personModel->index(lastPersonSelection,4),b);
    personModel->setData(personModel->index(lastPersonSelection,5),d);
    personModel->setData(personModel->index(lastPersonSelection,6),imageBlob);
    buttonEnabledFunct();
}

void MainWindow::onEditComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b)
{
    this->setEnabled(true);
    computerModel->setData(computerModel->index(lastCompSelection,0),id);
    computerModel->setData(computerModel->index(lastCompSelection,1),n);
    computerModel->setData(computerModel->index(lastCompSelection,2),t);
    computerModel->setData(computerModel->index(lastCompSelection,3),d);
    computerModel->setData(computerModel->index(lastCompSelection,4),b);
    buttonEnabledFunct();
}

void MainWindow::on_actionSave_Changes_triggered()
{
    saveChanges();
}

void MainWindow::saveChanges()
{

    if(personModel->isDirty())
    {
        saveModel(personModel);

        for(int i = 0; i < personModel->rowCount(); i++)
        {
            ui->table_Person->showRow(i);
        }
    }

    if(computerModel->isDirty())
    {
        saveModel(computerModel);

        for(int i = 0; i < computerModel->rowCount(); i++)
        {
            ui->table_Comp->showRow(i);
        }

    }

    if(relationModel->isDirty())
    {
        saveModel(relationModel);

    }
    ui->pushButton_Revert->setEnabled(true);
}

void MainWindow::revertChanges()
{
    if(personModel->isDirty())
    {
        personModel->revertAll();

        for(int i = 0; i < personModel->rowCount(); i++)
        {
            ui->table_Person->showRow(i);
        }
    }

    if(computerModel->isDirty())
    {
        computerModel->revertAll();

        for(int i = 0; i < computerModel->rowCount(); i++)
        {
            ui->table_Comp->showRow(i);
        }

    }
    if(relationModel->isDirty())
    {
        relationModel->revertAll();
        int index = ui->tabsWidget_personComputer->currentIndex();
        if(index == 0)
        {
            loadPersonInfo();
        }
        else if(index == 1)
        {
            loadComputerInfo();
        }
    }
}

void MainWindow::saveModel(QSqlRelationalTableModel * model)
{
    domain.submitDatabaseChanges(model);
}

void MainWindow::personRightClick()
{
    QMenu *pContextMenu = new QMenu(this);
    pContextMenu->addAction(ui->menuEdit->actions().at(0));
    pContextMenu->addAction(ui->menuEdit->actions().at(2));
    pContextMenu->exec(QCursor::pos());
}

void MainWindow::computerRightClick()
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
        for(int i = 0; i < selList.size(); i++)
        {
            ui->table_Person->hideRow(selList[i].row());
            QModelIndex realRow = proxyPersonModel->mapToSource(selList[i]);
            personModel->removeRow(realRow.row());
        }
    }
    else if(index == 1)//computer
    {
        QModelIndexList selList = ui->table_Comp->selectionModel()->selectedRows();
        for(int i = 0; i < selList.size(); i++)
        {

            ui->table_Comp->hideRow(selList[i].row());
            QModelIndex realRow = proxyCompModel->mapToSource(selList[i]);
            computerModel->removeRow(realRow.row());
        }
    }
    buttonEnabledFunct();
}

void MainWindow::on_actionDelete_triggered()
{
    deleteSelected();
    changesMade = 1;
}

QList<int> MainWindow::getPersonRelationId(int id){

    QList<int> computerId;
    for(int i = 0; i < relationModel->rowCount(); i++){
        QModelIndex personIdIndex = relationModel->index(i,1);
        QModelIndex ComputerIdIndex = relationModel->index(i,2);
        if(relationModel->data(personIdIndex, Qt::DisplayRole).toInt() == id){
            computerId.push_back(relationModel->data(ComputerIdIndex, Qt::DisplayRole).toInt());
        }
    }
    return computerId;
}

QList<int> MainWindow::getComputerRelationId(int id){

    QList<int> personId;
    for(int i = 0; i < relationModel->rowCount(); i++){
        QModelIndex personIdIndex = relationModel->index(i,1);
        QModelIndex ComputerIdIndex = relationModel->index(i,2);
        if(relationModel->data(ComputerIdIndex, Qt::DisplayRole).toInt() == id){
            personId.push_back(relationModel->data(personIdIndex, Qt::DisplayRole).toInt());
        }
    }
    return personId;
}

void MainWindow::hideAllRowsExcept(QTableView* table, QList<int> rowsNotToHide){

    for(int i = 0; i <= table->model()->rowCount(); i++ ){
        int id = table->model()->index(i,0).data().toInt();
        if(!rowsNotToHide.contains(id)){
            table->hideRow(i);
        }else{
            table->showRow(i);
        }
    }
}


void MainWindow::loadPersonInfo ()
{
    ui->computerInfo->hide();
    QString name = "<h3>"+(ui->table_Person->model()->index(lastPersonSelection,1).data().toString())+"</h3>";
    ui->label_name_pi->setText(name);
    ui->label_nation_pi->setText(ui->table_Person->model()->index(lastPersonSelection,3).data().toString());
    ui->label_born_pi->setText(ui->table_Person->model()->index(lastPersonSelection,4).data().toString());
    ui->label_deathage_pi->setText(ui->table_Person->model()->index(lastPersonSelection,5).data().toString());

    QByteArray imageData = QByteArray::fromBase64(ui->table_Person->model()->index(lastPersonSelection,6).data().toString().toLocal8Bit());
    QImage img;
    if (img.loadFromData(imageData)) {
        // show this label somewhere.
        QLabel image_personInfo;
        ui->image_personInfo->setPixmap(QPixmap::fromImage(img));
        ui->image_personInfo->setScaledContents(true);
    }else
    {
        ui->image_personInfo->clear();
    }

    QList<int> relList = getPersonRelationId(ui->table_Person->model()->index(lastPersonSelection,0).data().toInt());
    loadPITable();
    hideAllRowsExcept(ui->tablePI, relList);


    ui->personInfoWidget->show();
}

void MainWindow::loadComputerInfo()
{

    ui->personInfoWidget->hide();
    QString name = "<h3>"+ui->table_Comp->model()->index(lastCompSelection,1).data().toString()+"</h3>";
    ui->label_name_ci->setText(name);
    ui->label_type_ci->setText(ui->table_Comp->model()->index(lastCompSelection,2).data().toString());
    ui->label_dy_ci->setText(ui->table_Comp->model()->index(lastCompSelection,3).data().toString());
    ui->label_by_ci->setText(ui->table_Comp->model()->index(lastCompSelection,4).data().toString() );
    ui->computerInfo->show();

    QList<int> relList = getComputerRelationId(ui->table_Comp->model()->index(lastCompSelection,0).data().toInt());
    loadCITable();
    hideAllRowsExcept(ui->tableCI, relList);

}


void MainWindow::on_button_addPerson_clicked()
{
    addPersonDialog();
}

void MainWindow::on_button_addcomp_clicked()
{
    addComputerDialog();
}


void MainWindow::on_actionPersons_2_triggered()
{
    QString promptTitle = "DELETE ALL";
    QString promptQuestion = "Are you sure you want to delete every instance in Person table\nThis cannot be undone";
    QMessageBox::StandardButton prompt = QMessageBox::question(this,promptTitle, promptQuestion ,
                                                               QMessageBox::Yes|QMessageBox::No);

    if(prompt == QMessageBox::Yes)
    {
        personModel = domain.deletePersonTable();
        loadPersonTable();
    }
}

void MainWindow::on_actionComputers_2_triggered()
{
    QString promptTitle = "DELETE ALL";
    QString promptQuestion = "Are you sure you want to delete every instance in Computer table\nThis cannot be undone";
    QMessageBox::StandardButton prompt = QMessageBox::question(this,promptTitle, promptQuestion ,
                                                               QMessageBox::Yes|QMessageBox::No);
    if(prompt == QMessageBox::Yes)
    {
        computerModel = domain.deleteComputerTable();
        loadCompTable();
    }
}

void MainWindow::on_actionRelations_triggered()
{
    QString promptTitle = "DELETE ALL";
    QString promptQuestion = "Are you sure you want to delete every instance in Relation table\nThis cannot be undone";
    QMessageBox::StandardButton prompt = QMessageBox::question(this,promptTitle, promptQuestion ,
                                                               QMessageBox::Yes|QMessageBox::No);
    if(prompt == QMessageBox::Yes)
    {
        domain.deleteRelationTable();
        relationModel = domain.deleteRelationTable();
    }
}


void MainWindow::on_pushButton_editSelectedEntry_pressed()
{
    int index = ui->tabsWidget_personComputer->currentIndex();

    if(index == 0)//person
    {
        editPersonDialog();
    }
    else if(index == 1)//computer
    {
        editComputerDialog();
    }
}

void MainWindow::closeEvent()
{
    if(computerModel->isDirty() || personModel->isDirty() || relationModel->isDirty())
    {
        QString promptTitle = "Unsaved changes";
        QString promptQuestion = "Detected unsaved changes to database, do you want to save them";
        QMessageBox::StandardButton prompt = QMessageBox::question(this,promptTitle, promptQuestion ,
                                                                   QMessageBox::Yes|QMessageBox::No);
        if(prompt == QMessageBox::Yes)
        {
            saveChanges();
        }
        else if(prompt == QMessageBox::No)
        {

        }
    }
}

void MainWindow::on_pushButton_Delete_released()
{
    deleteSelected();

}

void MainWindow::on_addPersonRelation_released()
{
    QMap<QString, int> tList = domain.getAcceptedComputerTypeName();

    int id = ui->table_Person->model()->index(lastPersonSelection,0).data().toInt();
    QList<int> relList = getPersonRelationId(id);

    pRelDialogWindow = new CRelationP(proxyCompModel, relList, id, this);

    QObject::connect(pRelDialogWindow, SIGNAL(relationRejected()), this, SLOT(onDialogRejected()));
    QObject::connect(pRelDialogWindow,
                     SIGNAL(addPRelAccepted(const QList<int> &, const int &)),
                     this,
                     SLOT(onAddPRelAccepted(const QList<int> &, const int &)));

    this->setEnabled(false);
    pRelDialogWindow->setEnabled(true);
    pRelDialogWindow->show();
    changesMade = 1;
}

void MainWindow::on_addComputerRelation_released()
{
    QMap<QString, int> tList = domain.getAcceptedNationality();

    int id = ui->table_Comp->model()->index(lastCompSelection,0).data().toInt();
    QList<int> relList = getComputerRelationId(id);

    cRelDialogWindow = new PRelationC(proxyPersonModel, relList, id, this);

    QObject::connect(cRelDialogWindow, SIGNAL(relationRejected()), this, SLOT(onDialogRejected()));
    QObject::connect(cRelDialogWindow,
                     SIGNAL(addCRelAccepted(const QList<int> &, const int &)),
                     this,
                     SLOT(onAddCRelAccepted(const QList<int> &, const int &)));

    this->setEnabled(false);
    cRelDialogWindow->setEnabled(true);
    cRelDialogWindow->show();
    changesMade = 1;
}

void MainWindow::onAddPRelAccepted(const QList<int> &l, const int &id)
{
    QSqlRecord record = relationModel->record();

    foreach(int i, l){
        record.setValue(1,id);
        record.setValue(2,i);
        relationModel->insertRecord(-1,record);
    }

    QList<int> relList = getPersonRelationId(id);
    hideAllRowsExcept(ui->tablePI, relList);

}

void MainWindow::onAddCRelAccepted(const QList<int> &l, const int &id)
{
    QSqlRecord record = relationModel->record();

    foreach(int i, l){
        record.setValue(1,i);
        record.setValue(2,id);
        relationModel->insertRecord(-1,record);
    }

    QList<int> relList = getComputerRelationId(id);
    hideAllRowsExcept(ui->tableCI, relList);

}

void MainWindow::on_tabsWidget_personComputer_tabBarClicked(int index)
{
    clearAllSelection();
}

void MainWindow::clearAllSelection()
{
    ui->table_Comp->selectionModel()->clearSelection();
    ui->table_Person->selectionModel()->clearSelection();

    ui->pushButton_Delete->setEnabled(false);
    ui->actionDelete->setEnabled(false);

    ui->pushButton_editSelectedEntry->setEnabled(false);
    ui->actionEdit_Computer->setEnabled(false);
    ui->actionEdit_person->setEnabled(false);

    ui->personInfoWidget->setVisible(false);
    ui->computerInfo->setVisible(false);
}

void MainWindow::on_pushButton_Revert_released()
{
    revertChanges();
    buttonEnabledFunct();
}

void MainWindow::on_deletePersonRelation_released()
{
    deleteSelectedRelations();
}

void MainWindow::deleteSelectedRelations()
{
    int index = ui->tabsWidget_personComputer->currentIndex();

    if(index == 0)//person
    {
        QModelIndexList selList = ui->tablePI->selectionModel()->selectedRows();
        for(int i = 0; i < selList.size(); i++)
        {
            ui->tablePI->hideRow(selList[i].row());
            QModelIndex realRow = proxyPIModel->mapToSource(selList[i]);
            relationModel->removeRow(realRow.row());
        }
    }
    else if(index == 1)//computer
    {
        QModelIndexList selList = ui->tableCI->selectionModel()->selectedRows();
        for(int i = 0; i < selList.size(); i++)
        {
            ui->tableCI->hideRow(selList[i].row());
            QModelIndex realRow = proxyCIModel->mapToSource(selList[i]);
            relationModel->removeRow(realRow.row());
        }
    }
}

void MainWindow::buttonEnabledFunct()
{
    QModelIndexList pSelList = ui->table_Person->selectionModel()->selectedRows();
    QModelIndexList cSelList = ui->table_Comp->selectionModel()->selectedRows();
    if(pSelList.size() > 1 || cSelList.size() > 1)
    {
        ui->pushButton_editSelectedEntry->setEnabled(false);
        ui->actionEdit_person->setEnabled(false);

        ui->pushButton_Delete->setEnabled(true);
        ui->actionDelete->setEnabled(true);
    }
    else if(pSelList.size() == 1 || pSelList.size() == 1)
    {
        ui->pushButton_editSelectedEntry->setEnabled(true);
        ui->actionEdit_person->setEnabled(true);

        ui->pushButton_Delete->setEnabled(true);
        ui->actionDelete->setEnabled(true);
    }
    else
    {
        ui->pushButton_editSelectedEntry->setEnabled(false);
        ui->actionEdit_person->setEnabled(false);

        ui->pushButton_Delete->setEnabled(false);
        ui->actionDelete->setEnabled(false);
    }

    if(relationModel->isDirty() || computerModel->isDirty() || personModel->isDirty() == true)
    {
        ui->pushButton_Revert->setEnabled(true);
    }
    else
    {
        ui->pushButton_Revert->setEnabled(false);
    }
}
