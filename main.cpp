#include <QApplication>
// #include "gui.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    //UI ui;
    //ui.mainMenu();
    QApplication program(argc, argv);
  //  Gui gui;
  //  gui.show();

    MainWindow mainwindow;

    mainwindow.show();

    return program.exec();
}
