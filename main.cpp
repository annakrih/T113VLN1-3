#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication program(argc, argv);

    MainWindow mainwindow;
    mainwindow.show();

    return program.exec();
}
