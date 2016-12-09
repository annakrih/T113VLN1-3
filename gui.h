#ifndef GUI_H
#define GUI_H
#include <vector>
#include "utils.h"
#include "domain.h"

#include "personDialog.h"
#include "computerdialog.h"
#include "searchPersonDialog.h"


#include <QMainWindow>

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();

private slots:
    void on_addEditButton_clicked();
    void onNewPersonAccepted(const QString &n, const int &g, const QString &nat, const int &b, const int &d);
    void onEditPersonAccepted(const int &id, const QString &n, const int &g, const QString &nat, const int &b, const int &d);
    void onComputerAccepted(const QString &n, const int &t, const int &d, const int &b);
    void onEditComputerAccepted(const int &id, const QString &n, const int &t, const int &d, const int &b);

    void onPersonRejected();
    void onComputerRejected();

    void onSelectionChange(const QItemSelection &a, const QItemSelection &b);

    void on_saveButton_released();

    void on_deleteButton_released();

    void on_revertButton_released();

    void on_comboBox_currentIndexChanged(int index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_searchButton_released();

private:
    Ui::Gui *ui;
    PersonDialog *personDialogWindow;
    ComputerDialog *computerDialogWindow;
    Domain domain;
    Utils utils;
    QSqlRelationalTableModel* personModel;
    QSqlRelationalTableModel* computerModel;

    int lastSelection;
    bool overrideOnSelectionChange;

    enum Mode {Person, Computer};
    Mode currentMode = Person;

    void checkStatus();

    void loadTopTable(QSqlRelationalTableModel * model);
    void loadBottomTable(QSqlQueryModel * model);
    SearchPersonDialog *searchPersonDialogWindow;

    void switchToPerson();
    void switchToComputer();

    void saveModel(QSqlRelationalTableModel * model);
    void revertModel(QSqlRelationalTableModel * model);

    void onAddPersonButton();

    void onEditPersonButton();

    void onAddComputerButton();

    void onEditComputerButton();
};

#endif // GUI_H
