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
    void on_inputName_textChanged(const QString &arg1);

    void on_inputNat_textChanged(const QString &arg1);

    void on_inputBYFrom_editingFinished();

    void on_inputBYTo_editingFinished();

    void on_inputDYFrom_editingFinished();

    void on_inputDYTo_editingFinished();

private:
    Ui::SearchPersonDialog *ui;
    Utils utils;
};



#endif // SEARCHPERSONDIALOG_H
