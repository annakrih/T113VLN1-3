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
    //class for add/edit person window dialog
    class PersonDialog;
}

class PersonDialog : public QDialog
{
    Q_OBJECT

public:
    //default constructor
    //gets list of genders and nationality, which are used to populate comboboxes.
    //when personDialog is being used to edit a person, optional parameters take in name, gender, nationality etc.
    //so that they can be filled in ready to change.
    explicit PersonDialog(QWidget *parent, QMap<QString, int> gMap, QMap<QString, int> natMap, QString n = "", QString g = "", QString nat = "", int b = 0, int d = 0, QString pic = "", int id = 0);

    //deconstructor
    ~PersonDialog();

    //fills gender drop down menu with gender names/chars in gender table in database
    void fillGenderMenu(QMap<QString, int> gMap);
    //fills nationality menu with nationality names in nationality table in database
    void fillNationalityMenu(QMap<QString, int> natMap);

    //checks to see if enough entries have been input
    void checkForm();

private slots:
    //triggers ok and cancel buttons and x(close) (they both emit signals that the mainWindow is listening to)
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_PersonDialog_finished(int result);

    //each of these triggers calls a function that validates all inputs.
    void on_personName_textChanged(const QString &arg1);
    void on_personGender_currentIndexChanged(int index);
    void on_check_isAlive_clicked(bool isAlive);
    void on_personNat_currentIndexChanged(const int &arg1);
    void on_personBY_valueChanged(int arg1);
    void on_personDY_valueChanged(int arg1);

    //checks to see if user input can't be correct
    //for example if year inputs are higher then current year or if person died before they were born
    void on_personBY_editingFinished();
    void on_personDY_editingFinished();

    //button to add photo
    void on_inputPhoto_clicked();


signals:
    //signals that the mainWindow is listening to.

    //addPersonAccepted sends person parameters to the mainWindow, used in mainWindow::onAddPersonAccepted
    void addPersonAccepted(const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &fn);

    //addPersonAccepted sends person parameters to the mainWindow, used in mainWindow::onEditPersonAccepted
    void editPersonAccepted(const int &id, const QString &n, const int &g, const int &nat, const int &b, const int &d, const QString &fn);

    //signals mainWindow that user either cancelled or closed the dialog. (x in the corner)
    void personRejected();

private:
    Ui::PersonDialog *ui;
    QString fileName;
    Utils utils;
};

#endif // PERSONDIALOG_H
