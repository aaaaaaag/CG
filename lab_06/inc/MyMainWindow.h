//
// Created by denis on 18.04.2021.
//

#ifndef LAB_05_MYMAINWINDOW_H
#define LAB_05_MYMAINWINDOW_H

#include "QMainWindow"
#include "MainWindowUI.h"

#include "CanvasPolygon.h"

enum class colors
{
    Black = 0,
    White,
    Red,
    Green,
    Blue,
    Yellow
};

enum class Delay
{
    WithDelay = 0,
    WithoutDelay
};

class MyMainWindow: public QMainWindow {
    //Q_OBJECT

public:

    MyMainWindow();

    ~MyMainWindow();

private slots:

    void AddDotToCanvas(QMouseEvent* event);

private:

    void SetColors();
    void SetDelay();
    void SetComboColors();
    void SetComboDelay();

    void ConnectAllButtons();

    void SetCanvas();
    void connectAll();

    std::map<colors, std::string> m_mColorsToString;
    std::map<Delay, std::string> m_mDelayToString;
    Ui::MainWindow* m_pMainWindowUI;
    CanvasPolygon* m_pCanvas;
};


#endif //LAB_05_MYMAINWINDOW_H
