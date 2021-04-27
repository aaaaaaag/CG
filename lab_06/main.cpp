#include <iostream>
#include <QtWidgets/QApplication>
#include "inc/MyMainWindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    auto menu = new MyMainWindow();
    menu->show();
    return app.exec();
}
