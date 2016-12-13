#ifndef PERSONDIALOG_H
#define PERSONDIALOG_H

#include <QDialog>
#include "utils.h"

namespace Ui {
class PersonDialog;
}

class PersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PersonDialog(QWidget *parent, QMap<QString, int> gMap, QMap<QString, int> natMap, QString n = "", QString g = "", QString nat = "", int b = 0, int d = 0, int id = 0);
    ~PersonDialog();
    void fillGenderMenu(QMap<QString, int> gMap);
    void fillNationalityMenu(QMap<QString, int> natMap);
    void checkForm();

private slots:
    void on_buttonBox_accepted();
    void on_personName_textChanged(const QString &arg1);

    void on_personNat_currentIndexChanged(const int &arg1);

    void on_personBY_editingFinished();

    void on_personDY_editingFinished();

    void on_personCheckDY_toggled(bool checked);

    void on_personGender_currentIndexChanged(int index);

    void on_buttonBox_rejected();

    void on_PersonDialog_finished(int result);

    void on_personBY_valueChanged(int arg1);

    void on_personDY_valueChanged(int arg1);

    void on_textEdit_textChanged();

    void on_inputPhoto_clicked();

signals:
    void addPersonAccepted(const QString &n, const int &g, const int &nat, const int &b, const int &d);
    void editPersonAccepted(const int &id, const QString &n, const int &g, const int &nat, const int &b, const int &d);
    void personRejected();

private:
    Ui::PersonDialog *ui;
    Utils utils;
};

#endif // PERSONDIALOG_H
