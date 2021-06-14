#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QColorDialog>
#include <QMessageBox>
#include <QPixmapCache>
#include <iostream>
#include <QDebug>
//#include <windows.h>
#include <math.h>
#include <stack>
#include <stdlib.h>

#define OFFSET_X 10
#define OFFSET_Y 15

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->draw_label->setPalette(Qt::white);
    ui->draw_label->setMouseTracking(true);
    this->setMouseTracking(true);

    scene = new QPixmap(900, 900);
    scene->fill(QColor("transparent"));
    scene->fill(QColor(Qt::white));

    painter = new QPainter(scene);
    painter->setPen(QPen(Qt::black));

    ui->draw_label->setPixmap(*scene);

    QPalette Pal(palette());
    color_line = QColor(Qt::black);


    Pal.setColor(QPalette::Background, Qt::black);
    ui->frame_otr->setAutoFillBackground(true);
    ui->frame_otr->setPalette(Pal);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete painter;
    delete scene;
}

void MainWindow::on_pushButton_clicked()
{
    color_line = QColorDialog::getColor(Qt::black, this);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, color_line);
    ui->frame_otr->setAutoFillBackground(true);
    ui->frame_otr->setPalette(Pal);
    ui->frame_otr->show();
}



void MainWindow::on_clear_button_clicked()
{

    delete painter;
    delete scene;
    ui->draw_label->clear();
    scene = new QPixmap(900,900);
    scene->fill(QColor(Qt::white));
    painter = new QPainter(scene);
    ui->draw_label->setPixmap(*scene);
    fig_flag = false;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if (!fig_flag)
        return;

    if (event->key() == Qt::Key_S)
    {
        alphax -= 5;
    }
    else if (event->key() == Qt::Key_D)
    {
        alphay -= 5;
    }
    else if (event->key() == Qt::Key_A)
    {
        alphay += 5;
    }
    else if (event->key() == Qt::Key_W)
    {
        alphax += 5;
    }
    else if (event->key() == Qt::Key_E)
    {
        alphaz += 5;
    }
    else if (event->key() == Qt::Key_Z)
    {
        alphaz -= 5;
    }
    on_clear_button_clicked();
    params p(xbegin,xend,xdelta,ybegin,yend,ydelta);
    p.alphax =alphax;
    p.alphay = alphay;
    p.alphaz = alphaz;
    int i = ui->comboBox->currentIndex();
    p.func = Func.get_f(i);
    painter->setPen(color_line);
    horizon_alg(p,*painter);
    ui->draw_label->setPixmap(*scene);
    fig_flag = true;

}
void MainWindow::on_shading_button_clicked()
{

}
void MainWindow::on_background_button_clicked(){}

void MainWindow::on_pushButton_3_clicked()
{
    painter->setPen(color_line);
    double x = ui->xbegin->value();
    double x1 = ui->xend->value();
    double x2 = ui->xdelta->value();
    double y = ui->zbegin->value();
    double y1 = ui->zend->value();
    double y2 = ui->zdelta->value();

    xbegin = x;
    xend = x1;
    xdelta = x2;
    ybegin = y;
    yend = y1;
    ydelta = y2;

    on_clear_button_clicked();

    alphax = 0;
    alphay = 0;
    alphaz = 0;

    params p(xbegin,xend,xdelta,ybegin,yend,ydelta);
    p.alphax =alphax;
    p.alphay = alphay;
    p.alphaz = alphaz;
    int i = ui->comboBox->currentIndex();
    p.func = Func.get_f(i);
    painter->setPen(color_line);
    horizon_alg(p,*painter);
    ui->draw_label->setPixmap(*scene);
    fig_flag = true;
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!fig_flag)
        return;
    int ax = ui->alphax->value();
    int ay = ui->alphay->value();
    int az = ui->alphay_2->value();

    on_clear_button_clicked();
    alphax += ax;
    alphay += ay;
    alphaz += az;
    params p(xbegin,xend,xdelta,ybegin,yend,ydelta);
    p.alphax =alphax;
    p.alphay = alphay;
    p.alphaz = alphaz;
    int i = ui->comboBox->currentIndex();
    p.func = Func.get_f(i);
    painter->setPen(color_line);
    horizon_alg(p,*painter);
    ui->draw_label->setPixmap(*scene);
    fig_flag = true;
}
