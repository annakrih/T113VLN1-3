#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include "utils.h"
#include "domain.h"
#include <string>
#include <iostream>
#include <QMessageBox>

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

    void on_comboBox_currentIndexChanged(int index);
    void fillSearchComboBoxC();
    void on_searchComboBox_currentIndexChanged(int index);
    void loadPersonTable(QSqlRelationalTableModel * model);
    void loadCompTable(QSqlRelationalTableModel * model);


private slots:

    void on_comboBox_searchPerson_currentIndexChanged(int index);

    void on_comboBox_searchComputer_currentIndexChanged(int index);

    void on_searchInput_Person_textEdited(const QString& searchString);

    void on_searchInput_Comp_textEdited(const QString &searchString);

    void on_button_advSearchPerson_released();

private:
    Ui::MainWindow *ui;
    int currentPersonSearchIndex = 0;
    int currentCompSearchIndex = 0;
    bool showMoreFilterOpsPersons = 0;
//    bool showMoreFilterOpsComps = 0;
    Domain domain;
    QSqlRelationalTableModel* personModel;
    QSqlRelationalTableModel* computerModel;

    void searchPerson(const QString& searchInput);
    void searchComp(const QString& searchInput);

};

#endif // MAINWINDOW_H
