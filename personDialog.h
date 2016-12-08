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
    explicit PersonDialog(QWidget *parent, QMap<QString, int> gMap, QString n = "", QString g = "", QString nat = "", int b = 0, int d = 0, int id = 0);
    ~PersonDialog();
    void fillGenderMenu(QMap<QString, int> gMap);
    void fillNationalityMenu();
    void checkForm();

private slots:
    void on_buttonBox_accepted();
    void on_entryName_textChanged(const QString &arg1);

    void on_entryNationality_textChanged(const QString &arg1);

    void on_entryBY_editingFinished();

    void on_entryDY_editingFinished();

    void on_entryCheckDY_toggled(bool checked);

    void on_entryGender_currentIndexChanged(int index);

    void on_buttonBox_rejected();

    void on_PersonDialog_finished(int result);

signals:
    void newPersonAccepted(const QString &n, const int &g, const QString &nat, const int &b, const int &d);
    void editPersonAccepted(const int &id, const QString &n, const int &g, const QString &nat, const int &b, const int &d);
    void personEntryRejected();

private:
    Ui::PersonDialog *ui;
    Utils utils;
};

#endif // PERSONDIALOG_H
