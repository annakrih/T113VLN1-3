#ifndef SEARCHPERSONDIALOG_H
#define SEARCHPERSONDIALOG_H

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

private:
    Ui::SearchPersonDialog *ui;
};

#endif // SEARCHPERSONDIALOG_H
