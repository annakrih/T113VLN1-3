#ifndef COMPUTERDIALOG_H
#define COMPUTERDIALOG_H

#include "utils.h"

#include <QDialog>
#include <QMap>

namespace Ui {
class computerDialog;
}

class computerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit computerDialog(QWidget *parent = 0, QMap<int, QString> tList = QMap<int,QString>{});

private slots:
    void on_wasItBuilt_toggled(bool checked);

private:
    Ui::computerDialog *ui;
    Utils utils;
    void checkForm();
    void fillTypeMenu(QMap<int, QString> tList);
};

#endif // COMPUTERDIALOG_H
