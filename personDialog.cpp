#include "personDialog.h"
#include "ui_personDialog.h"

#include <string>
#include <iostream>
#include <QPushButton>

PersonDialog::PersonDialog(QWidget *parent, QMap<QString,int> gMap, QString n, QString g, QString nat, int b, int d, int id) :
    QDialog(parent),
    ui(new Ui::PersonDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    fillGenderMenu(gMap);

    ui->hiddenId->setValue(id);
    ui->entryName->setFocus();
    ui->entryName->setText(n);
    ui->entryGender->setCurrentText(g);
    ui->entryNationality->setText(nat);
    ui->entryBY->setValue(b);
    if(!d){
        ui->entryCheckDY->setChecked(false);
    }else{
        ui->entryDY->setValue(d);
    }

    checkForm();
}

PersonDialog::~PersonDialog()
{
    delete ui;
}

void PersonDialog::on_buttonBox_accepted()
{
    QString name = ui->entryName->text().trimmed();
    int gender =  ui->entryGender->itemData(ui->entryGender->currentIndex()).toInt();
    QString nationality = ui->entryNationality->text().trimmed();
    int bY = ui->entryBY->value();
    int dY;
    if(ui->entryCheckDY->checkState() && ui->entryBY->value() != 0){
        dY = ui->entryDY->value();
    }else if(!ui->entryCheckDY->checkState()){
        dY = 0;
    }
    int id = ui->hiddenId->value();

    if(id == 0){//add
        emit this->newPersonAccepted(name,gender,nationality,bY,dY);
    }else{//edit
        emit this->editPersonAccepted(id,name,gender,nationality,bY,dY);
    }
}

void PersonDialog::fillGenderMenu(QMap<QString,int> gMap){

    ui->entryGender->addItem("",0);
    QMapIterator<QString, int> i(gMap);
    i.toBack();
    while (i.hasPrevious()) {
        i.previous();
        ui->entryGender->addItem(i.key(),i.value());
    }

};

void PersonDialog::fillNationalityMenu(){
    for ( int i = 1; i < 256; i++ )
    {
       QLocale::Country foo = static_cast<QLocale::Country>(i);
       QString test = QLocale::countryToString(foo);

       //ui->entryGender->addItem(i.key(),i.value());
    }
}

void PersonDialog::checkForm(){
    const int needed = 5;
    int count = 0;

    if(ui->entryName->text() != "") count++;
    if(ui->entryGender->itemData(ui->entryGender->currentIndex()).toInt() != 0) count++;
    if(ui->entryNationality->text() != "") count++;
    if(ui->entryBY->value() != 0) count++;
    if(ui->entryCheckDY->checkState() && ui->entryBY->value() != 0){
        count++;
    }else if(!ui->entryCheckDY->checkState()){
        count++;
    }

    if(count >= needed){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }else{
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }

}

void PersonDialog::on_entryName_textChanged(const QString &arg1)
{
    if(arg1.length() && arg1[arg1.length() - 1] != ' '){
        QString text = utils.capitalizeString(arg1);
        ui->entryName->setText(text);
    }
    checkForm();
}

void PersonDialog::on_entryNationality_textChanged(const QString &arg1)
{
    if(arg1.length() && arg1[arg1.length() - 1] != ' '){
        QString text = utils.capitalizeString(arg1);
        ui->entryNationality->setText(text);
    }
    checkForm();
}

void PersonDialog::on_entryBY_editingFinished()
{
    int bY = ui->entryBY->value();
    int dY = ui->entryDY->value();
    if(bY > dY){
        ui->entryDY->setValue(bY);
    }
    checkForm();
}

void PersonDialog::on_entryDY_editingFinished()
{
    int bY = ui->entryBY->value();
    int dY = ui->entryDY->value();
    if(bY > dY){
        ui->entryDY->setValue(bY);
    }
    checkForm();
}

void PersonDialog::on_entryCheckDY_toggled(bool checked)
{
    if(checked){
        ui->entryDY->setDisabled(false);
    }else{
        ui->entryDY->setDisabled(true);
    }
    checkForm();
}

void PersonDialog::on_entryGender_currentIndexChanged(int index)
{
    checkForm();
}

void PersonDialog::on_buttonBox_rejected()
{
    emit this->personEntryRejected();
}

void PersonDialog::on_PersonDialog_finished(int result)
{
    emit this->personEntryRejected();
}
