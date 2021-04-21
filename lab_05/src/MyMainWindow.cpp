//
// Created by denis on 18.04.2021.
//

#include "../inc/MyMainWindow.h"
#include "../inc/CanvasPolygon.h"
MyMainWindow::MyMainWindow() {
    m_pMainWindowUI = new Ui::MainWindow;
    m_pMainWindowUI->setupUi(this);
    SetColors();
    SetDelay();
    SetComboColors();
    SetComboDelay();


    SetCanvas();
    connectAll();

    ConnectAllButtons();
}

MyMainWindow::~MyMainWindow() {
    delete m_pMainWindowUI;
}

void MyMainWindow::connectAll() {

    //connect(m_pCanvas, SIGNAL(pressedMouse(QMouseEvent *)), this, SLOT(myMousePressEvent(QMouseEvent *)));
}

void MyMainWindow::SetCanvas() {
    m_pCanvas = new CanvasPolygon(m_pMainWindowUI);
    m_pMainWindowUI->horizontalLayoutMain->addWidget(m_pCanvas);
}

void MyMainWindow::AddDotToCanvas(QMouseEvent *event) {
    m_pCanvas->DrawLine();
}

void MyMainWindow::SetColors() {
    m_mColorsToString.emplace(colors::Black, "Чёрный");
    m_mColorsToString.emplace(colors::White, "Белый");
    m_mColorsToString.emplace(colors::Red, "Красный");
    m_mColorsToString.emplace(colors::Green, "Зелёный");
    m_mColorsToString.emplace(colors::Blue, "Синий");
    m_mColorsToString.emplace(colors::Yellow, "Жёлтый");
}

void MyMainWindow::SetComboColors() {
    for (auto color: m_mColorsToString)
        m_pMainWindowUI->comboBoxColor_9->addItem(color.second.data());
}

void MyMainWindow::SetDelay() {
    m_mDelayToString.emplace(Delay::WithDelay, "С задержкой");
    m_mDelayToString.emplace(Delay::WithoutDelay, "Без задержки");
}

void MyMainWindow::SetComboDelay() {
    for (auto delay: m_mDelayToString)
        m_pMainWindowUI->comboBoxDelay_9->addItem(delay.second.data());
}

void MyMainWindow::ConnectAllButtons() {
    //connect(m_pMainWindowUI->buttonDeleteLastAction_9, &QPushButton::clicked, m_pCanvas, &CanvasPolygon::clear);
    connect(m_pMainWindowUI->buttonClearCanvas_9, SIGNAL(clicked()), m_pCanvas, SLOT(Clear()));
    connect(m_pMainWindowUI->buttonDeleteLastAction_9, SIGNAL(clicked()), m_pCanvas, SLOT(DeleteLastDot()));
    connect(m_pMainWindowUI->buttonLockFigure_9, SIGNAL(clicked()), m_pCanvas, SLOT(LockAndFill()));
}
