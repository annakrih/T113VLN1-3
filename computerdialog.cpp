#include "computerdialog.h"
#include "ui_computerdialog.h"
#include <QPushButton>
#include <QMap>
#include <QVariant>

computerDialog::computerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::computerDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    //fillTypeMenu(tList);
}



void computerDialog::on_wasItBuilt_toggled(bool checked)
{
    if(checked){
        ui->buildYInput->setDisabled(false);
    }else{
        ui->buildYInput->setDisabled(true);
    }
    checkForm();
}

void computerDialog::checkForm()
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

void computerDialog::fillTypeMenu(QMap<int, QString> tList)
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
