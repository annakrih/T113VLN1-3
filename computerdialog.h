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
    explicit ComputerDialog(QWidget *parent = 0, QMap<int, QString> tList = QMap<int,QString>{}, QString n = "", QString t = "", int dy = 0, int by = 0, int id = 0);
    void fillTypeMenu(QMap<int, QString> tList);
    void checkForm();

private slots:
    void on_wasItBuilt_toggled(bool checked);

private:
    Ui::ComputerDialog *ui;
    Utils utils;


signals:
    void newComputerAccepted(const QString &n, const QString &t, const int &dy, const int &by, const int &id);
    void editComputerAccepted(const QString &n, const QString &t, const int &dy, const int &by, const int &id);
    void computerEntryRejected();
};

#endif // COMPUTERDIALOG_H
