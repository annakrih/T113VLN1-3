#include "searchPersonDialog.h"
#include "ui_searchPersonDialog.h"

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
