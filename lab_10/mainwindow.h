#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QColorDialog>
#include <QMessageBox>
#include <QPixmapCache>
#include <iostream>
//#include <windows.h>
#include <stack>
#include <vector>
#include <math.h>
#include <QColor>
#include <QPainter>
#include "f.h"
#include "alg.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_shading_button_clicked();

    void on_background_button_clicked();

    void on_clear_button_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();



private:

    Ui::MainWindow *ui;
    QPainter *painter;
    QPixmap *scene;
    QColor color_otr;
    QColor color_line;
    QColor color_ots;
    QPoint position;
    myfunc func;
    Function Func;

    double xbegin, xend, xdelta;
    double ybegin, yend, ydelta;
    double alphax, alphay, alphaz;
    bool fig_flag = false;


    QImage img;
};

#endif // MAINWINDOW_H
