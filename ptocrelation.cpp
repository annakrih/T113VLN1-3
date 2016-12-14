#include "ptocrelation.h"
#include "ui_ptocrelation.h"

PToCRelation::PToCRelation(QWidget *parent) :
    QDialog(parent),
   ui(new Ui::PToCRelation)
{
    ui->setupUi(this);
}

PToCRelation::~PToCRelation()
{
    delete ui;
}
