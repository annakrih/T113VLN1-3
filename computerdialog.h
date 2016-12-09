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
    explicit ComputerDialog(QWidget *parent = 0, QMap<int, QString> tList = QMap<int,QString>{} ,
                            QString n = "", QString t = 0, int d = 0, int b = 0, int id = 0);

private slots:
    void on_buttonBox_accepted();
    void on_wasItBuilt_toggled(bool checked);
    void on_buttonBox_rejected();
    void on_ComputerDialog_finished(int result);

signals:
    void newComputerAccepted(const QString &n, const int &t, const int &d, const int &b);
    void editComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b);
    void computerRejected();


private:
    Ui::ComputerDialog *ui;
    Utils utils;
    void checkForm();
    void fillTypeMenu(QMap<int, QString> tList);
};

#endif // COMPUTERDIALOG_H
