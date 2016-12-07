#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include "utils.h"
#include "domain.h"
#include "person.h"
#include "computer.h"
#include "addEntry.h"


#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addEntry_clicked();
    void onNewEntryAccepted(const QString &n, const int &g, const QString &nat, const int &b, const int &d);
    void onNewEntryRejected();
    void on_tableWidget_itemClicked();

private:
    Ui::MainWindow *ui;
    AddEntry *addEntryWindow;
    Domain domain;
    Utils utils;

    int lastSelectedRow = utils.dummyNull;
    int editEntry = utils.dummyNull;

    void loadPersonTable(vector<Person> pList);
};

#endif // MAINWINDOW_H
