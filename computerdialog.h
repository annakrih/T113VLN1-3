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
class ComputerDialog;
}

class ComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerDialog(QWidget *parent = 0, QMap<QString, int> tList = QMap<QString, int>{} ,
                            QString n = "", QString t = 0, int d = 0, int b = 0, int id = 0);


private slots:
    void on_buttonBox_accepted();
    void on_wasItBuilt_toggled(bool checked);
    void on_buttonBox_rejected();
    void on_ComputerDialog_finished();

    void on_cName_textChanged();

    void on_cType_currentIndexChanged();

    void on_cDY_valueChanged();

    void on_cBY_valueChanged();

    void on_cDY_editingFinished();

    void on_cBY_editingFinished();

signals:
    void addComputerAccepted(const QString &n, const int &t, const int &d, const int &b);
    void editComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b);
    void computerRejected();


private:
    Ui::ComputerDialog *ui;
    Utils utils;
    void checkForm();
    void fillTypeMenu(QMap<QString, int> tList);

    void loadPersonTable();

};

#endif // COMPUTERDIALOG_H
