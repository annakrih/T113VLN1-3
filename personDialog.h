#ifndef PERSONDIALOG_H
#define PERSONDIALOG_H

#include <QDialog>
#include "utils.h"
#include <string>
#include <iostream>
#include <QPushButton>
#include <Qpixmap>
#include <QFileDialog>

namespace Ui
{
class PersonDialog;
}

class PersonDialog : public QDialog
{
    Q_OBJECT

public:
    //default constructor
    explicit PersonDialog(QWidget *parent, QMap<QString, int> gMap, QMap<QString, int> natMap, QString n = "", QString g = "", QString nat = "", int b = 0, int d = 0, int id = 0);

    //deconstructor
    ~PersonDialog();

    //fills gender drop down menu with gender names/chars in gender table in database
    void fillGenderMenu(QMap<QString, int> gMap);
    //fills nationality menu with nationality names in nationality table in database
    void fillNationalityMenu(QMap<QString, int> natMap);

    //checks to see if enough entries have been input
    void checkForm();

private slots:
    //ok and cancel buttons
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    //closing window
    void on_PersonDialog_finished(int result);

    //calls a function that checks if all inputs have been filled
    void on_personName_textChanged(const QString &arg1);
    void on_personGender_currentIndexChanged(int index);
    void on_personNat_currentIndexChanged(const int &arg1);
    void on_personCheckDY_toggled(bool checked);
    void on_personBY_valueChanged(int arg1);
    void on_personDY_valueChanged(int arg1);

    //checks to see if user input can't be correct
    //fx if year inputs are higher then current year or if person died before they were born
    void on_personBY_editingFinished();
    void on_personDY_editingFinished();

    //button to add photo
    void on_inputPhoto_clicked();

signals:
    //a function that adds new person
    void addPersonAccepted(const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &fn);

    //function to edit valid computer
    void editPersonAccepted(const int &id, const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &fn);

    //signal to mainwindow
    void personRejected();

private:
    Ui::PersonDialog *ui;
    QString fileName;
    Utils utils;
};

#endif // PERSONDIALOG_H
