#include "personinfo.h"
#include "ui_personinfo.h"

personInfo::personInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::personInfo)
{
    ui->setupUi(this);
}

personInfo::~personInfo()
{
    delete ui;
}
