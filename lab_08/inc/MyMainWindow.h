//
// Created by denis on 18.04.2021.
//

#ifndef LAB_05_MYMAINWINDOW_H
#define LAB_05_MYMAINWINDOW_H

#include "QMainWindow"
#include "MainWindowUI.h"

#include "CanvasPolygon.h"

class MyMainWindow: public QMainWindow {
    //Q_OBJECT

public:

    MyMainWindow();

    ~MyMainWindow();

private slots:

    void AddDotToCanvas(QMouseEvent* event);

private:

    void ConnectAllButtons();

    void SetCanvas();
    void connectAll();

    Ui::MainWindow* m_pMainWindowUI;
    CanvasPolygon* m_pCanvas;
};


#endif //LAB_05_MYMAINWINDOW_H
