#include "searchComputerDialog.h"
#include "ui_searchComputerDialog.h"

SearchComputerDialog::SearchComputerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchComputerDialog)
{
    ui->setupUi(this);
}

SearchComputerDialog::~SearchComputerDialog()
{
    delete ui;
}
