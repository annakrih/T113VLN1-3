#include "searchPersonDialog.h"
#include "ui_searchPersonDialog.h"
#include <iostream>
using namespace std;

SearchPersonDialog::SearchPersonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchPersonDialog)
{
    ui->setupUi(this);
}

SearchPersonDialog::~SearchPersonDialog()
{
    delete ui;
}

void SearchPersonDialog::on_inputName_textChanged(const QString &arg1)
{
    if(arg1.length() && arg1[arg1.length() - 1] != ' '){
        QString text = utils.capitalizeString(arg1);
        ui->inputName->setText(text);
    }
}

void SearchPersonDialog::on_inputNat_textChanged(const QString &arg1)
{
    if(arg1.length() && arg1[arg1.length() - 1] != ' '){
        QString text = utils.capitalizeString(arg1);
        ui->inputNat->setText(text);
    }
}

//birth year search from
void SearchPersonDialog::on_inputBYFrom_editingFinished()
{
    int fromVal = ui->inputBYFrom->value();
    int toVal =  ui->inputBYTo->value();

    if(fromVal>=toVal)
    {
       ui->inputBYTo->setValue(fromVal);
    }
}

//birth year search to
void SearchPersonDialog::on_inputBYTo_editingFinished()
{

    int fromVal = ui->inputBYFrom->value();
    int toVal =  ui->inputBYTo->value();

    if(fromVal>=toVal)
    {
       ui->inputBYTo->setValue(fromVal);
    }
}

//death year search from
void SearchPersonDialog::on_inputDYFrom_editingFinished()
{
    int fromVal = ui->inputDYFrom->value();
    int toVal =  ui->inputDYTo->value();

    if(fromVal>=toVal)
    {
       ui->inputDYTo->setValue(fromVal);
    }
}

//death year search to
void SearchPersonDialog::on_inputDYTo_editingFinished()
{
    int fromVal = ui->inputDYFrom->value();
    int toVal =  ui->inputDYTo->value();

    if(fromVal>=toVal)
    {
       ui->inputDYTo->setValue(fromVal);
    }
}
