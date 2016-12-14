#include "ctoprelation.h"
#include "ui_ctoprelation.h"

CToPRelation::CToPRelation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CToPRelation)
{
    ui->setupUi(this);
}

CToPRelation::~CToPRelation()
{
    delete ui;
}
