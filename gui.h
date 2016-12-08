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
    void on_personAddEdit_clicked();
    void onNewPersonAccepted(const QString &n, const int &g, const QString &nat, const int &b, const int &d);
    void onEditPersonAccepted(const int &id, const QString &n, const int &g, const QString &nat, const int &b, const int &d);
    void onPersonEntryRejected();

    void on_tableView_clicked(const QModelIndex &index);

    void on_savePerson_clicked();

    void on_deletePerson_released();

    void on_peopleRevert_released();

    void on_comboBox_currentIndexChanged(int index);


private:
    Ui::Gui *ui;
    PersonDialog *personDialogWindow;
    ComputerDialog *computerDialogWindow;
    Domain domain;
    Utils utils;
    QSqlRelationalTableModel* personModel;

    int lastSelectedRow = utils.dummyNull;

    void loadTopTable(QSqlRelationalTableModel * model);
    SearchPersonDialog *searchPersonDialogWindow;
};

#endif // GUI_H
