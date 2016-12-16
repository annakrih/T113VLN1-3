#ifndef COMPUTERDIALOG_H
#define COMPUTERDIALOG_H

#include "utils.h"
#include <QDialog>
#include <QMap>
#include "ui_computerdialog.h"
#include <QPushButton>
#include <QVariant>
#include <iostream>

#include "personDialog.h"
#include "computerdialog.h"

namespace Ui
{
    //class for add/edit computer dialog window
    class ComputerDialog;
}

class ComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerDialog(QWidget *parent = 0, QMap<QString, int> tList = QMap<QString, int>{} ,
                            QString n = "", QString t = 0, int d = 0, int b = 0, int id = 0);

private slots:
    //ok and cancel buttons
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    //closing window
    void on_ComputerDialog_finished(int result);    

    //triggers that call a function that checks if all required inputs have been filled and are valid
    void on_cName_textChanged(const QString &arg1);
    void on_cType_currentIndexChanged(const QString &arg1);
    void on_cBY_editingFinished();
    void on_cDY_editingFinished();

    //disables the build year input if checked, and enables it when unchecked.
    //Then triggers a function that checks if all required inputs are valid
    void on_wasItBuilt_clicked(bool checked);

    //disables the OK option while the build year is being edited and
    //clears the error message if there was one.
    //after editing of buildyear is finished it is checked if the input is valid.
    void on_cBY_valueChanged(int arg1);
signals:
    //function that adds new computer
    void addComputerAccepted(const QString &n, const int &t, const int &d, const int &b);

    //function to edit valid computer
    void editComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b);

    //signal to mainwindow
    void computerRejected();

private:
    Ui::ComputerDialog *ui;
    Utils utils;

    //function that checks if all entries have been filled
    void checkForm();

    //fills the type drop down menu with the types in the database
    void fillTypeMenu(QMap<QString, int> tList);
};

#endif // COMPUTERDIALOG_H



