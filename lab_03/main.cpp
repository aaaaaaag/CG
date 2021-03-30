#include <iostream>
#include <QtWidgets/QApplication>
#include <Qt/MainMenu.h>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    auto menu = new MainMenu();
    menu->show();
    return app.exec();
}
