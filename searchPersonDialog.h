#ifndef SEARCHPERSONDIALOG_H
#define SEARCHPERSONDIALOG_H
#include "utils.h"

#include <QDialog>

namespace Ui {
class SearchPersonDialog;
}

class SearchPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchPersonDialog(QWidget *parent = 0);
    ~SearchPersonDialog();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_spinBox_5_editingFinished();

    void on_spinBox_6_editingFinished();

    void on_spinBox_2_editingFinished();

    void on_spinBox_8_editingFinished();

private:
    Ui::SearchPersonDialog *ui;
    Utils utils;
};



#endif // SEARCHPERSONDIALOG_H
