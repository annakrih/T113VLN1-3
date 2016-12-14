#include "computerdialog.h"

ComputerDialog::ComputerDialog(QWidget *parent, QMap<QString, int> tList,
                               QString n, QString t, int d, int b, int id) :
    QDialog(parent),
    ui(new Ui::ComputerDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->cBY->setDisabled(true);
    ui->wasItBuilt->setChecked(true);
    ui->cBY->setMaximum(utils.getYear);
    ui->cDY-> setMaximum(utils.getYear);

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
            ui->wasItBuilt->setChecked(true);
        }
        else
        {
            ui->cDY->setValue(b);
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
    if(ui->wasItBuilt->checkState() && ui->cBY->value() != 0)
    {
        bY = ui->cBY->value();
    }
    else if(!ui->wasItBuilt->checkState())
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
}

void ComputerDialog::on_wasItBuilt_toggled(bool checked)
{
    if(checked)
    {
        ui->cBY->setDisabled(false);
    }else
    {
        ui->cBY->setDisabled(true);
    }
    checkForm();
}

void ComputerDialog::checkForm()
{
    const int needed = 4;
    int count = 0;

    if(ui->cName->text() != "")
    {
        count++;
    }
    if(ui->cType->itemData(ui->cType->currentIndex()).toInt() != 0)
    {
        count++;
    }
    if(ui->cDY->value() != 0)
    {
        count++;
    }
    if(ui->wasItBuilt->checkState() && ui->cBY->value() != 0)
    {
        count++;
    }
    else if(!ui->wasItBuilt->checkState())
    {
        count++;
    }

    if(count >= needed)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }

}

void ComputerDialog::fillTypeMenu(QMap<QString, int> tList)
{
    ui->cType->addItem(0,"");
    QMapIterator<QString, int> i(tList);
    i.toBack();
    while (i.hasPrevious())
    {
        i.previous();
        ui->cType->addItem(i.key(), i.value());
    }
}

void ComputerDialog::on_buttonBox_rejected()
{
    this->close();
    emit this->computerRejected();
}

void ComputerDialog::on_ComputerDialog_finished(int result)
{
    emit this->computerRejected();
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

void ComputerDialog::on_cDY_valueChanged(int arg1)
{
    checkForm();
}

void ComputerDialog::on_cBY_valueChanged(int arg1)
{
    checkForm();
}

void ComputerDialog::on_cDY_editingFinished()
{
    int cDY = ui->cDY->value();
    int cBY = ui->cBY->value();
    if(cDY > cBY)
    {
        ui->cBY->setValue(cDY);
    }
    checkForm();
}

void ComputerDialog::on_cBY_editingFinished()
{
    int cDY = ui->cDY->value();
    int cBY = ui->cBY->value();
    if(cDY > cBY)
    {
        ui->cBY->setValue(cDY);
    }
    checkForm();
}
