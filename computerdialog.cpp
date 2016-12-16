#include "computerdialog.h"

ComputerDialog::ComputerDialog(QWidget *parent, QMap<QString, int> tList,
                               QString n, QString t, int d, int b, int id) :
    QDialog(parent),
    ui(new Ui::ComputerDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->cBY->setDisabled(false);
    ui->wasItBuilt->setChecked(false);
    ui->cBY->setMaximum(utils.getYear);
    ui->cDY-> setMaximum(utils.getYear);

    ui->errorMessage->setStyleSheet("QLabel {color:red;}");

    fillTypeMenu(tList);

    if(id)
    {
        ui->hiddenId->setValue(id);
        ui->cName->setFocus();
        ui->cName->setText(n);
        ui->cType->setCurrentText(t);
        ui->cDY->setValue(d);
        if(!b)
        {
            ui->wasItBuilt->setChecked(false);
        }
        else
        {
            ui->cBY->setValue(b);
        }
    }
    ui->hiddenId->setDisabled(true);
    checkForm();
}

void ComputerDialog::on_buttonBox_accepted()
{
    QString name = ui->cName->text().trimmed();
    int type =  ui->cType->itemData(ui->cType->currentIndex()).toInt();
    int dY = ui->cDY->value();
    int bY;
    if(!ui->wasItBuilt->checkState() && ui->cBY->value() != 0)
    {
        bY = ui->cBY->value();
    }
    else if(ui->wasItBuilt->checkState())
    {
        bY = 0;
    }

    int id = ui->hiddenId->value();

    if(id == 0)//add
    {
        emit this->addComputerAccepted(name,type,dY,bY);
    }
    else//edit
    {
        emit this->editComputerAccepted(id,name,type,dY,bY);
    }
    this->close();
}

void ComputerDialog::checkForm()
{
    bool entriesValid=1;
    int designYear = ui->cDY->value();
    int buildYear = ui->cBY->value();

    if(ui->cName->text() == "")//name needs to be filled
    {
        entriesValid = 0;
    }
    if(ui->cType->itemData(ui->cType->currentIndex()).toInt() == 0)//type needs to be filled
    {
        entriesValid = 0;
    }
    if(designYear == 0)//design year needs to be filled
    {
        entriesValid = 0;
    }

    ui->errorMessage->setText("");
    if(!ui->wasItBuilt->checkState())
    {
        if(buildYear<designYear) //build year cannot be smaller than design year
        {
            entriesValid = 0;
            if (!(buildYear==0))
            {
            ui->errorMessage->setText("Build year cannot be before design year.");
            }
        }
    }

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(entriesValid);
}

void ComputerDialog::fillTypeMenu(QMap<QString, int> tList)
{
    ui->cType->addItem(0,"");
    QMapIterator<QString, int> i(tList);
    i.toBack();
    //fetching type names from computer types table in database
    while (i.hasPrevious())
    {
        i.previous();
        ui->cType->addItem(i.key(), i.value());
    }
}

void ComputerDialog::on_buttonBox_rejected()
{
    emit this->computerRejected();
    this->close();
}

void ComputerDialog::on_ComputerDialog_finished(int result)
{
    emit this->computerRejected();
    this->close();
}

void ComputerDialog::on_cName_textChanged(const QString &arg1)
{
    //no capitalize string function is called here because computers can have for example all caps names
    //user must enter correct name
    checkForm();
}

void ComputerDialog::on_cType_currentIndexChanged(const QString &arg1)
{
    checkForm();
}


void ComputerDialog::on_cDY_editingFinished()
{
    checkForm();
}

void ComputerDialog::on_cBY_editingFinished()
{
    checkForm();
}

void ComputerDialog::on_cBY_valueChanged(int arg1)
{
   ui->errorMessage->setText("");
   ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

void ComputerDialog::on_wasItBuilt_clicked(bool wasNotBuilt)
{
    ui->cBY->setEnabled(!wasNotBuilt);
    checkForm();
}
