#include "personDialog.h"
#include "ui_personDialog.h"

#include <string>
#include <iostream>
#include <QPushButton>
#include <Qpixmap>
#include <QFileDialog>

PersonDialog::PersonDialog(QWidget *parent, QMap<QString,int> gMap,QMap<QString, int> natMap, QString n, QString g, QString nat, int b, int d, int id) :
    QDialog(parent),
    ui(new Ui::PersonDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    fillGenderMenu(gMap);
    fillNationalityMenu(natMap);

    if(id){
        ui->hiddenId->setValue(id);
        ui->personName->setFocus();
        ui->personName->setText(n);
        ui->personGender->setCurrentText(g);
        ui->personNat->setCurrentText(nat);
        ui->personBY->setValue(b);
        if(!d)
        {
            ui->personCheckDY->setChecked(false);
        }
        else
        {
            ui->personDY->setValue(d);
        }
    }

    checkForm();
}

PersonDialog::~PersonDialog()
{
    delete ui;
}

void PersonDialog::on_buttonBox_accepted()
{
    QString name = ui->personName->text().trimmed();
    int gender =  ui->personGender->itemData(ui->personGender->currentIndex()).toInt();
    int nationality = ui->personNat->itemData(ui->personNat->currentIndex()).toInt();;
    int bY = ui->personBY->value();
    int dY;
    if(ui->personCheckDY->checkState() && ui->personBY->value() != 0)
    {
        dY = ui->personDY->value();
    }
    else if(!ui->personCheckDY->checkState())
    {
        dY = 0;
    }
    int id = ui->hiddenId->value();

    if(id == 0)//add
    {
        emit this->addPersonAccepted(name,gender,nationality,bY,dY);
    }
    else//edit
    {
        emit this->editPersonAccepted(id,name,gender,nationality,bY,dY);
    }
}

void PersonDialog::fillGenderMenu(QMap<QString,int> gMap)
{

    ui->personGender->addItem("",0);
    QMapIterator<QString, int> i(gMap);
    i.toBack();
    while (i.hasPrevious())
    {
        i.previous();
        ui->personGender->addItem(i.key(),i.value());
    }

}

void PersonDialog::fillNationalityMenu(QMap<QString,int> natList){

    ui->personNat->addItem("",0);
    QMapIterator<QString, int> i(natList);
    while (i.hasNext())
    {
        i.next();
        ui->personNat->addItem(i.key(),i.value());
    }

}

void PersonDialog::checkForm()
{
    const int needed = 5;
    int count = 0;

    if(ui->personName->text() != "") count++;
    if(ui->personGender->itemData(ui->personGender->currentIndex()).toInt() != 0) count++;
    if(ui->personNat->currentText() != "") count++;
    if(ui->personBY->value() != 0) count++;
    if(ui->personCheckDY->checkState() && ui->personBY->value() != 0){
        count++;
    }else if(!ui->personCheckDY->checkState())
    {
        count++;
    }

    if(count >= needed)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }

}

void PersonDialog::on_personName_textChanged(const QString &arg1)
{
    if(arg1.length() && arg1[arg1.length() - 1] != ' ')
    {
        QString text = utils.capitalizeString(arg1);
        ui->personName->setText(text);
    }
    checkForm();
}

void PersonDialog::on_personNat_currentIndexChanged(const int &arg1)
{
    checkForm();
}

void PersonDialog::on_personBY_editingFinished()
{
    int bY = ui->personBY->value();
    int dY = ui->personDY->value();
    if(bY > dY)
    {
        ui->personDY->setValue(bY);
    }
    checkForm();
}

void PersonDialog::on_personDY_editingFinished()
{
    int bY = ui->personBY->value();
    int dY = ui->personDY->value();
    if(bY > dY)
    {
        ui->personDY->setValue(bY);
    }
    checkForm();
}

void PersonDialog::on_personCheckDY_toggled(bool checked)
{
    if(checked)
    {
        ui->personDY->setDisabled(false);
    }else
    {
        ui->personDY->setDisabled(true);
    }
    checkForm();
}

void PersonDialog::on_personGender_currentIndexChanged(int index)
{
    checkForm();
}

void PersonDialog::on_buttonBox_rejected()
{
    this->close();
    emit this->personRejected();
}

void PersonDialog::on_PersonDialog_finished(int result)
{
    emit this->personRejected();
}

void PersonDialog::on_personBY_valueChanged(int arg1)
{
    checkForm();
}

void PersonDialog::on_personDY_valueChanged(int arg1)
{
    checkForm();
}

void PersonDialog::on_textEdit_textChanged()
{
    checkForm();
}

void PersonDialog::on_inputPhoto_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "/home",
                                                    "Images (*.png *.xpm *.jpg)");
    std::cout << fileName.toStdString();
}
