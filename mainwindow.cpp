#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //TODO setWindowTitle("newTitle");
    ui->setupUi(this);
    this->setStyleSheet(domain.getCssString());
    ui->personInfoWidget->setVisible(false);
    ui->computerInfo->setVisible(false);

    personModel = domain.getPersonModel();
    computerModel = domain.getComputerModel();
    proxyPersonModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyCompModel->setSortCaseSensitivity(Qt::CaseInsensitive);


    ui->table_Person->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_Comp->setSelectionBehavior(QAbstractItemView::SelectRows);

    loadPersonTable();
    loadCompTable();

    fillNationalitySearchBox(domain.getAcceptedNationality());
    fillComputerTypeSearchBox(domain.getAcceptedComputerTypeName());

    showAdvSearchPersons = 0;
    ui->widget_advancedSearchPerson->setVisible(showAdvSearchPersons);

    showAdvSearchComps = 0;
    ui->widget_advancedSearchComp->setVisible(showAdvSearchComps);

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

    connect(ui->table_Person,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(personRightClick()));
    connect(ui->table_Comp,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(computerRightClick()));
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
    ui->table_Person->setColumnHidden(6,true);
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

void MainWindow::loadRelationTable()
{

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


void MainWindow::on_input_searchPerson_textEdited()
{
    searchPerson();
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

void MainWindow::searchComp()
{
    QString searchNameInput = ui->searchInput_Comp->text();

    if(showAdvSearchComps)
    {
        QString DYfrom = ui->input_searchDesignYearFrom->text();
        QString DYto = ui->input_searchDesignYearTo->text();
        QString BYfrom = ui->input_searchBuildYearFrom->text();
        QString BYto = ui->input_searchBuildYearTo->text();
        QString compType = ui->input_searchCompType->itemData(ui->input_searchCompType->currentIndex()).toString();

        computerModel= domain.searchComputer(searchNameInput, DYfrom, DYto, BYfrom, BYto, compType);
    }
    else
    {
        computerModel = domain.searchComputer(searchNameInput);
    }
    loadCompTable();
}


void MainWindow::on_searchInput_Comp_textEdited()
{
    searchComp();
}

void MainWindow::on_input_searchDesignYearFrom_editingFinished()
{
    searchComp();
}

void MainWindow::on_input_searchDesignYearTo_editingFinished()
{
    searchComp();
}

void MainWindow::on_input_searchBuildYearFrom_editingFinished()
{
    searchComp();
}

void MainWindow::on_input_searchBuildYearTo_editingFinished()
{
    searchComp();
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
    }

    showAdvSearchPersons = !showAdvSearchPersons;
    ui->widget_advancedSearchPerson->setVisible(showAdvSearchPersons);
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

void MainWindow::on_input_searchCompType_currentIndexChanged(const QString &arg1)
{
    searchComp();
}


void MainWindow::on_input_searchDiedFrom_editingFinished()
{
    searchPerson();
}

void MainWindow::on_input_searchDiedTo_editingFinished()
{
    searchPerson();
}

void MainWindow::on_input_searchNat_currentIndexChanged(const QString &arg1)
{
    searchPerson();
}

void MainWindow::on_table_Person_clicked(const QModelIndex &index)
{

    if(lastPersonSelection == index.row() && !overrideTableClick)
    {
        overrideOnPersonSelectionChange = true;
        ui->table_Person->selectionModel()->clearSelection();
        lastPersonSelection = -1;
        ui->personInfoWidget->setVisible(false);
        overrideOnPersonSelectionChange = false;
    }
    overrideTableClick = false;
}

void MainWindow::onPersonSelectionChange()
{
    if(!overrideOnPersonSelectionChange && !ui->table_Person->selectionModel()->selectedRows().isEmpty())
    {
        int index = ui->table_Person->currentIndex().row();
        lastPersonSelection = index;
        overrideTableClick = true;
        loadPersonInfo();
    }
}


void MainWindow::on_table_Comp_clicked(const QModelIndex &index)
{

    if(lastCompSelection == index.row() && !overrideTableClick)
    {
        overrideOnCompSelectionChange = true;
        ui->table_Comp->selectionModel()->clearSelection();
        lastCompSelection = -1;
        ui->computerInfo->setVisible(false);
        overrideOnCompSelectionChange = false;
    }
    overrideTableClick = false;

}

void MainWindow::onCompSelectionChange()
{
    if(!overrideOnCompSelectionChange && !ui->table_Comp->selectionModel()->selectedRows().isEmpty())
    {
        int index = ui->table_Comp->currentIndex().row();
        lastCompSelection = index;
        overrideTableClick = true;
        loadComputerInfo();
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

void MainWindow::on_actionAdd_new_relation_triggered()
{
    addRelationDialog();
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

    QObject::connect(personDialogWindow, SIGNAL(personRejected()), this, SLOT(onPersonRejected()));
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

    QObject::connect(computerDialogWindow, SIGNAL(computerRejected()), this, SLOT(onComputerRejected()));
    QObject::connect(computerDialogWindow,
                     SIGNAL(addComputerAccepted(const QString &, const int &, const int &, const int &)),
                     this,
                     SLOT(onAddComputerAccepted(const QString &, const int &, const int &, const int &)));

    this->setEnabled(false);
    computerDialogWindow->setEnabled(true);
    computerDialogWindow->show();
    changesMade = 1;
}

void MainWindow::addRelationDialog()
{

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

    QObject::connect(computerDialogWindow, SIGNAL(computerRejected()), this, SLOT(onComputerRejected()));
    QObject::connect(computerDialogWindow,
                     SIGNAL(editComputerAccepted(const int &,const QString &, const int &, const int &, const int &)),
                     this,
                     SLOT(onEditComputerAccepted(const int &,const QString &, const int &, const int &, const int &)));

    this->setEnabled(false);
    computerDialogWindow->setEnabled(true);
    computerDialogWindow->show();
    changesMade = 1;
}


void MainWindow::onPersonRejected()
{
    this->setEnabled(true);
}

void MainWindow::onComputerRejected()
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
    record.setValue(1,n);
    record.setValue(2,g);
    record.setValue(3,nat);
    record.setValue(4,b);
    record.setValue(5,d);
    record.setValue(6,imageBlob);
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
}

void MainWindow::on_actionDelete_triggered()
{
    deleteSelected();
    changesMade = 1;
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
        domain.getDeletePersonTable();
        personModel = domain.getPersonModel();
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
        domain.getDeleteComputerTable();
        computerModel = domain.getComputerModel();
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
        domain.getDeleteRelationTable();
        //TODO relationModel = domain.getRelationModel();
        //TODO loadRelationModel();
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

void MainWindow::on_input_searchBornFrom_textEdited(const QString &arg1)
{
    QString newString;
    for(int i = 0; i < arg1.size(); i++)
    {
        if(arg1[i] == '1' || arg1[i] == '2' || arg1[i] == '3' || arg1[i] == '4' || arg1[i] == '5' || arg1[i] == '6' || arg1[i] == '7' || arg1[i] == '8' || arg1[i] == '9' || arg1[i] == '0')
        {
            newString += arg1[i];
        }
    }
    ui->input_searchBornFrom->setText(newString);
}

void MainWindow::on_input_searchBornTo_textEdited(const QString &arg1)
{
    QString newString;
    for(int i = 0; i < arg1.size(); i++)
    {
        if(arg1[i] == '1' || arg1[i] == '2' || arg1[i] == '3' || arg1[i] == '4' || arg1[i] == '5' || arg1[i] == '6' || arg1[i] == '7' || arg1[i] == '8' || arg1[i] == '9' || arg1[i] == '0')
        {
            newString += arg1[i];
        }
    }
    ui->input_searchBornTo->setText(newString);
}

void MainWindow::on_input_searchDiedFrom_textEdited(const QString &arg1)
{
    QString newString;
    for(int i = 0; i < arg1.size(); i++)
    {
        if(arg1[i] == '1' || arg1[i] == '2' || arg1[i] == '3' || arg1[i] == '4' || arg1[i] == '5' || arg1[i] == '6' || arg1[i] == '7' || arg1[i] == '8' || arg1[i] == '9' || arg1[i] == '0')
        {
            newString += arg1[i];
        }
    }
    ui->input_searchDiedFrom->setText(newString);
}

void MainWindow::on_input_searchDiedTo_textEdited(const QString &arg1)
{
    QString newString;
    for(int i = 0; i < arg1.size(); i++)
    {
        if(arg1[i] == '1' || arg1[i] == '2' || arg1[i] == '3' || arg1[i] == '4' || arg1[i] == '5' || arg1[i] == '6' || arg1[i] == '7' || arg1[i] == '8' || arg1[i] == '9' || arg1[i] == '0')
        {
            newString += arg1[i];
        }
    }
    ui->input_searchDiedTo->setText(newString);
}

void MainWindow::on_input_searchDesignYearFrom_textEdited(const QString &arg1)
{
    QString newString;
    for(int i = 0; i < arg1.size(); i++)
    {
        if(arg1[i] == '1' || arg1[i] == '2' || arg1[i] == '3' || arg1[i] == '4' || arg1[i] == '5' || arg1[i] == '6' || arg1[i] == '7' || arg1[i] == '8' || arg1[i] == '9' || arg1[i] == '0')
        {
            newString += arg1[i];
        }
    }
    ui->input_searchDesignYearFrom->setText(newString);
}

void MainWindow::on_input_searchDesignYearTo_textEdited(const QString &arg1)
{
    QString newString;
    for(int i = 0; i < arg1.size(); i++)
    {
        if(arg1[i] == '1' || arg1[i] == '2' || arg1[i] == '3' || arg1[i] == '4' || arg1[i] == '5' || arg1[i] == '6' || arg1[i] == '7' || arg1[i] == '8' || arg1[i] == '9' || arg1[i] == '0')
        {
            newString += arg1[i];
        }
    }
    ui->input_searchDesignYearTo->setText(newString);
}

void MainWindow::on_input_searchBuildYearFrom_textEdited(const QString &arg1)
{
    QString newString;
    for(int i = 0; i < arg1.size(); i++)
    {
        if(arg1[i] == '1' || arg1[i] == '2' || arg1[i] == '3' || arg1[i] == '4' || arg1[i] == '5' || arg1[i] == '6' || arg1[i] == '7' || arg1[i] == '8' || arg1[i] == '9' || arg1[i] == '0')
        {
            newString += arg1[i];
        }
    }
    ui->input_searchBuildYearFrom->setText(newString);
}

void MainWindow::on_input_searchBuildYearTo_textEdited(const QString &arg1)
{
    QString newString;
    for(int i = 0; i < arg1.size(); i++)
    {
        if(arg1[i] == '1' || arg1[i] == '2' || arg1[i] == '3' || arg1[i] == '4' || arg1[i] == '5' || arg1[i] == '6' || arg1[i] == '7' || arg1[i] == '8' || arg1[i] == '9' || arg1[i] == '0')
        {
            newString += arg1[i];
        }
    }
    ui->input_searchBuildYearTo->setText(newString);
}

void MainWindow::loadRelation()
{

}


void MainWindow::closeEvent()
{
    if(computerModel->isDirty() || personModel->isDirty())
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

QString MainWindow::hasTableChanged()
{
    QString windowName = "";
    if(changesMade)
    {
        windowName = "MainWindow*";
    }
    else if(!changesMade)
    {
        windowName = "MainWindow";
    }
    return windowName;
}
