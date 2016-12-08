#ifndef SEARCHDOMPUTERDIALOG_H
#define SEARCHDOMPUTERDIALOG_H

#include <QDialog>

namespace Ui {
class SearchComputerDialog;
}

class SearchComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchComputerDialog(QWidget *parent = 0);
    ~SearchComputerDialog();

private:
    Ui::SearchComputerDialog *ui;
};

#endif // SEARCHDOMPUTERDIALOG_H
