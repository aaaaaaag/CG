#include "mainwindow.hpp"

#include <QApplication>
// /home/denis/alohov/4_sem/CG/9/cmake-build-debug/lab_04_debug_autogen/include/ui_mainwindow.h
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
