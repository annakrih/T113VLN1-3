#include "computerdialog.h"
#include "ui_computerdialog.h"
#include <QPushButton>
#include <QMap>
#include <QVariant>

ComputerDialog::ComputerDialog(QWidget *parent, QMap<int,QString> tList) :
    QDialog(parent),
    ui(new Ui::ComputerDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buildYInput->setDisabled(true);
    //ui->designYInput->maximum(utils.getYear);
    //ui->buildYInput->maximum(utils.getYear);


    fillTypeMenu(tList);
}



void ComputerDialog::on_wasItBuilt_toggled(bool checked)
{
    if(checked){
        ui->buildYInput->setDisabled(false);
    }else{
        ui->buildYInput->setDisabled(true);
    }
    checkForm();
}

void ComputerDialog::checkForm()
{
    const int needed = 4;
    int count = 0;

    if(ui->lineEdit->text() != "")
    {
        count++;
    }
    if(ui->cType->itemData(ui->cType->currentIndex()).toInt() != 0)
    {
        count++;
    }
    if(ui->designYInput->value() != 0)
    {
        count++;
    }
    if(ui->wasItBuilt->checkState() && ui->buildYInput->value() != 0)
    {
        count++;
    }
    else if(!ui->wasItBuilt->checkState()){
        count++;
    }

    if(count >= needed)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }

}

void ComputerDialog::fillTypeMenu(QMap<int, QString> tList)
{
    ui->cType->addItem(0,"");
    QMapIterator<int, QString> i(tList);
    i.toBack();
    while (i.hasPrevious())
    {
        i.previous();
        ui->cType->addItem(i.value(), i.key());
    }
}
