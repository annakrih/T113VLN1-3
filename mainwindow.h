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
    void on_searchComboBox_currentIndexChanged(int index);
    void loadPersonTable(QSqlRelationalTableModel * model);
    void loadCompTable(QSqlRelationalTableModel * model);


private slots:
    void on_input_searchPerson_textEdited();

    void on_searchInput_Comp_textEdited(const QString &searchString);

    void on_button_advSearchPerson_released();

    void on_checkBox_searchFemale_released();

    void on_checkBox_searchMale_released();

    void on_input_searchBornFrom_editingFinished();

    void on_input_searchBornTo_editingFinished();

    void on_input_searchDiedFrom_editingFinished();

    void on_input_searchDiedTo_editingFinished();

private:
    Ui::MainWindow *ui;
    int currentPersonSearchIndex = 0;
    int currentCompSearchIndex = 0;
    bool showAdvSearchPersons = 0;
//    bool showAdvSearchComps = 0;
    Domain domain;
    QSqlRelationalTableModel* personModel;
    QSqlRelationalTableModel* computerModel;

    void searchPerson();
    void searchComp(const QString& searchInput);

};

#endif // MAINWINDOW_H
