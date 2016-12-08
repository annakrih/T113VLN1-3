#ifndef COMPUTERDIALOG_H
#define COMPUTERDIALOG_H

#include "utils.h"

#include <QDialog>
#include <QMap>

namespace Ui {
class ComputerDialog;
}

class ComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerDialog(QWidget *parent = 0, QMap<int, QString> tList = QMap<int,QString>{});

private slots:
    void on_wasItBuilt_toggled(bool checked);

private:
    Ui::ComputerDialog *ui;
    Utils utils;
    void checkForm();
    void fillTypeMenu(QMap<int, QString> tList);
};

#endif // COMPUTERDIALOG_H
