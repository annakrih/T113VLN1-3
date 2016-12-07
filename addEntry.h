#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QDialog>
#include "utils.h"

namespace Ui {
class AddEntry;
}

class AddEntry : public QDialog
{
    Q_OBJECT

public:
    explicit AddEntry(QWidget *parent, QMap<QString, int> gMap, QString n = "", int g = 0, QString nat = "", int b = 0, int d = 0);
    ~AddEntry();
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

    void on_AddEntry_finished(int result);

signals:
    void newEntryAccepted(const QString &n, const int &g, const QString &nat, const int &b, const int &d);
    void newEntryRejected();

private:
    Ui::AddEntry *ui;
    Utils utils;
};

#endif // ADDENTRY_H
