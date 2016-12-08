#include <QApplication>
#include "gui.h"


int main(int argc, char *argv[])
{
    //UI ui;
    //ui.mainMenu();
    QApplication program(argc, argv);
    Gui gui;

    gui.show();


    return program.exec();
}
