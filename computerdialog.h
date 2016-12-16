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
//class for computer dialog
class ComputerDialog;
}

class ComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerDialog(QWidget *parent = 0, QMap<QString, int> tList = QMap<QString, int>{} ,
                            QString n = "", QString t = 0, int d = 0, int b = 0, int id = 0);

private slots:
    //
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    //closing window
    void on_ComputerDialog_finished(int result);    

    //calls a function that checks if all inputs have been filled
    void on_cName_textChanged(const QString &arg1);
    void on_cType_currentIndexChanged(const QString &arg1);
    void on_wasItBuilt_toggled(bool checked);
    void on_cDY_valueChanged(int arg1);
    void on_cBY_valueChanged(int arg1);

    void on_cDY_editingFinished();
    void on_cBY_editingFinished();

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
