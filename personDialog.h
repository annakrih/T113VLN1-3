#ifndef PERSONDIALOG_H
#define PERSONDIALOG_H

#include <QDialog>
#include "utils.h"
#include <string>
#include <iostream>
#include <QPushButton>
#include <Qpixmap>
#include <QFileDialog>

namespace Ui
{
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

    void on_personNat_currentIndexChanged();

    void on_personBY_editingFinished();

    void on_personDY_editingFinished();

    void on_personCheckDY_toggled(bool checked);

    void on_personGender_currentIndexChanged();

    void on_buttonBox_rejected();

    void on_PersonDialog_finished();

    void on_personBY_valueChanged();

    void on_personDY_valueChanged();

    void on_textEdit_textChanged();

    void on_inputPhoto_clicked();

signals:
    void addPersonAccepted(const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &fn);
    void editPersonAccepted(const int &id, const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &fn);
    void personRejected();

private:
    Ui::PersonDialog *ui;
    QString fileName;
    Utils utils;
};

#endif // PERSONDIALOG_H
