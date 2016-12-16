#include "personDialog.h"
#include "ui_personDialog.h"

PersonDialog::PersonDialog(QWidget *parent, QMap<QString,int> gMap, QMap<QString, int> natMap, QString n, QString g, QString nat, int b, int d, QString pic, int id) :
    QDialog(parent),
    ui(new Ui::PersonDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    fillGenderMenu(gMap);
    fillNationalityMenu(natMap);

    ui->errorMessage->setStyleSheet("QLabel {color:red;}");

    if(id)
    {
        ui->inputPhoto->setText("Edit Photo");
        ui->hiddenId->setValue(id);
        ui->personName->setFocus();
        ui->personName->setText(n);
        ui->personGender->setCurrentText(g);
        ui->personNat->setCurrentText(nat);
        ui->personBY->setValue(b);
        if(!d)
        {
            ui->check_isAlive->setChecked(true);
        }
        else
        {
            ui->personDY->setValue(d);
        }

        QByteArray imageData = QByteArray::fromBase64(pic.toLocal8Bit());
        QImage img;
        if (img.loadFromData(imageData)) {
            // show this label somewhere.
            ui->label_image->setPixmap(QPixmap::fromImage(img));
        }

    }
    ui->hiddenId->setDisabled(true);
    checkForm();
    fileName = "";
}

PersonDialog::~PersonDialog()
{
    delete ui;
}

void PersonDialog::on_buttonBox_accepted()
{
    QString name = ui->personName->text().trimmed();
    int gender =  ui->personGender->itemData(ui->personGender->currentIndex()).toInt();
    int nationality = ui->personNat->itemData(ui->personNat->currentIndex()).toInt();;
    int bY = ui->personBY->value();
    int dY;
    if(!ui->check_isAlive->checkState() && ui->personBY->value() != 0)
    {
        dY = ui->personDY->value();
    }
    else if(ui->check_isAlive->checkState())
    {
        dY = 0;
    }
    int id = ui->hiddenId->value();

    if(id == 0)//add
    {
        emit this->addPersonAccepted(name,gender,nationality,bY,dY,fileName);
    }
    else//edit
    {
        emit this->editPersonAccepted(id,name,gender,nationality,bY,dY,fileName);
    }

    this->close();
}

void PersonDialog::fillGenderMenu(QMap<QString,int> gMap)
{

    ui->personGender->addItem("",0);
    QMapIterator<QString, int> i(gMap);
    i.toBack();
    //fetching gender strings from database
    while (i.hasPrevious())
    {
        i.previous();
        ui->personGender->addItem(i.key(),i.value());
    }

}

void PersonDialog::fillNationalityMenu(QMap<QString,int> natList)
{
    ui->personNat->addItem("",0);
    QMapIterator<QString, int> i(natList);
    //fetches natinality strings from database
    while (i.hasNext())
    {
        i.next();
        ui->personNat->addItem(i.key(),i.value());
    }

}

void PersonDialog::checkForm()
{
    bool validInput = 1;

    int birthYear = ui->personBY->value();
    int deathYear = ui->personDY->value();

    if(ui->personName->text() == "")//name
    {
        validInput = 0;
    }
    if(ui->personGender->itemData(ui->personGender->currentIndex()).toInt() == 0) //gender
    {
        validInput = 0;
    }
    if(ui->personNat->currentText() == "")//nationality
    {
        validInput = 0;
    }
    if(birthYear == 0)//birth year
    {
        validInput = 0;
    }

    ui->errorMessage->setText("");
    if(!(ui->check_isAlive->checkState()))
    {
        if(deathYear<birthYear)
        {
            validInput = 0;
            if(!deathYear==0)
            {
                ui->errorMessage->setText("Death year cannot be before birth year.");
            }
        }
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(validInput);
}

void PersonDialog::on_personName_textChanged(const QString &arg1)
{
    //calls capitalize string to make first char in every word capitalized
    if(arg1.length() && arg1[arg1.length() - 1] != ' ')
    {
        QString text = utils.capitalizeString(arg1);
        ui->personName->setText(text);
    }
    checkForm();
}

void PersonDialog::on_personNat_currentIndexChanged(const int &arg1)
{
    checkForm();
}

void PersonDialog::on_personBY_editingFinished()
{
    checkForm();
}

void PersonDialog::on_personDY_editingFinished()
{
    checkForm();
}


void PersonDialog::on_personGender_currentIndexChanged(int index)
{
    checkForm();
}

void PersonDialog::on_buttonBox_rejected()
{
    emit this->personRejected();
    this->close();
}

void PersonDialog::on_PersonDialog_finished(int arg1)
{
    emit this->personRejected();
    this->close();
}

void PersonDialog::on_personBY_valueChanged(int arg1)
{
    ui->errorMessage->setText("");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

void PersonDialog::on_personDY_valueChanged(int arg1)
{
    checkForm();
}

void PersonDialog::on_inputPhoto_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Open File", "/home", "Images (*.png *.xpm *.jpg)");
    if (fileName.length())
    {
        //File selected
        QPixmap pixmap (fileName);
        ui->label_image->setPixmap(pixmap);
        ui->label_image->setScaledContents(true);
    }
}

void PersonDialog::on_check_isAlive_clicked(bool isAlive)
{
    ui->personDY->setEnabled(!isAlive);
    checkForm();
}
