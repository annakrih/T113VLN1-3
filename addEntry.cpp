#include "addEntry.h"
#include "ui_addEntry.h"

#include <string>
#include <QPushButton>

AddEntry::AddEntry(QWidget *parent, QMap<QString,int> gMap, QString n, int g, QString nat, int b, int d) :
    QDialog(parent),
    ui(new Ui::AddEntry)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    fillGenderMenu(gMap);

    ui->entryName->setFocus();
    ui->entryName->setText(n);
    ui->entryGender->setCurrentIndex(g);
    ui->entryNationality->setText(nat);
    ui->entryBY->setValue(b);
    if(!d){
        ui->entryCheckDY->setChecked(false);
    }else{
        ui->entryDY->setValue(b);
    }

    checkForm();
}

AddEntry::~AddEntry()
{
    delete ui;
}

void AddEntry::on_buttonBox_accepted()
{
    QString name = ui->entryName->text();
    int gender =  ui->entryGender->itemData(ui->entryGender->currentIndex()).toInt();
    QString nationality = ui->entryNationality->text();
    int bY = ui->entryBY->value();
    int dY;
    if(ui->entryCheckDY->checkState() && ui->entryBY->value() != 0){
        dY = ui->entryDY->value();
    }else if(!ui->entryCheckDY->checkState()){
        dY = 0;
    }

    emit this->newEntryAccepted(name,gender,nationality,bY,dY);
}

void AddEntry::fillGenderMenu(QMap<QString,int> gMap){

    ui->entryGender->addItem("",0);
    QMapIterator<QString, int> i(gMap);
    i.toBack();
    while (i.hasPrevious()) {
        i.previous();
        ui->entryGender->addItem(i.key(),i.value());
    }

};

void AddEntry::fillNationalityMenu(){
    for ( int i = 1; i < 256; i++ )
    {
       QLocale::Country foo = static_cast<QLocale::Country>(i);
       QString test = QLocale::countryToString(foo);

       //ui->entryGender->addItem(i.key(),i.value());
    }
}

void AddEntry::checkForm(){
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

void AddEntry::on_entryName_textChanged(const QString &arg1)
{
    if(arg1.length() && arg1[arg1.length() - 1] != ' '){
        QString text = utils.capitalizeString(arg1);
        ui->entryName->setText(text);
    }
    checkForm();
}

void AddEntry::on_entryNationality_textChanged(const QString &arg1)
{
    if(arg1.length() && arg1[arg1.length() - 1] != ' '){
        QString text = utils.capitalizeString(arg1);
        ui->entryNationality->setText(text);
    }
    checkForm();
}

void AddEntry::on_entryBY_editingFinished()
{
    int bY = ui->entryBY->value();
    int dY = ui->entryDY->value();
    if(bY > dY){
        ui->entryDY->setValue(bY);
    }
    checkForm();
}

void AddEntry::on_entryDY_editingFinished()
{
    int bY = ui->entryBY->value();
    int dY = ui->entryDY->value();
    if(bY > dY){
        ui->entryDY->setValue(bY);
    }
    checkForm();
}

void AddEntry::on_entryCheckDY_toggled(bool checked)
{
    if(checked){
        ui->entryDY->setDisabled(false);
    }else{
        ui->entryDY->setDisabled(true);
    }
    checkForm();
}

void AddEntry::on_entryGender_currentIndexChanged(int index)
{
    checkForm();
}

void AddEntry::on_buttonBox_rejected()
{
    emit this->newEntryRejected();
}

void AddEntry::on_AddEntry_finished(int result)
{
    emit this->newEntryRejected();
}
