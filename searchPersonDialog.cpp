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
