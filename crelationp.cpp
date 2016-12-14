#include "crelationp.h"
#include "ui_crelationp.h"

CrelationP::CrelationP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CrelationP)
{
    ui->setupUi(this);
}

CrelationP::~CrelationP()
{
    delete ui;
}
