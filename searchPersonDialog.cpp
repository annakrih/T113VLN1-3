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

void SearchPersonDialog::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.length() && arg1[arg1.length() - 1] != ' '){
        QString text = utils.capitalizeString(arg1);
        ui->lineEdit->setText(text);
    }
}

void SearchPersonDialog::on_lineEdit_6_textChanged(const QString &arg1)
{
    if(arg1.length() && arg1[arg1.length() - 1] != ' '){
        QString text = utils.capitalizeString(arg1);
        ui->lineEdit_6->setText(text);
    }
}

//birth year search from
void SearchPersonDialog::on_spinBox_5_editingFinished()
{
    int fromVal = ui->spinBox_5->value();
    int toVal =  ui->spinBox_5->value();

    if(fromVal>toVal)
    {
       // ui->spinBox_6->value(fromVal);
    }
}

//birth year search to
void SearchPersonDialog::on_spinBox_6_editingFinished()
{

    int fromVal = ui->spinBox_5->value();
    int toVal =  ui->spinBox_5->value();

    if(fromVal<=toVal)
    {
       // ui->spinBox_6->value(fromVal);
    }
}

//death year search from
void SearchPersonDialog::on_spinBox_2_editingFinished()
{
    int fromVal = ui->spinBox_2->value();
    int toVal =  ui->spinBox_2->value();
    if(fromVal<=toVal)
    {
       // ui->spinBox_2->value(fromVal);
    }
}

//death year search to
void SearchPersonDialog::on_spinBox_8_editingFinished()
{
    int fromVal = ui->spinBox_8->value();
    int toVal =  ui->spinBox_8->value();
    if(fromVal<=toVal)
    {
       // ui->spinBox_8->value(fromVal);
    }
}
