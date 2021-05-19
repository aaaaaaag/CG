//
// Created by denis on 18.04.2021.
//

#include "../inc/MyMainWindow.h"
#include "../inc/CanvasPolygon.h"
MyMainWindow::MyMainWindow() {
    m_pMainWindowUI = new Ui::MainWindow;


    m_pMainWindowUI->setupUi(this);

    SetCanvas();
    auto button = new QPushButton;
    button->setText("Замкнуть отсекатель");
    connect(button, SIGNAL(clicked()), m_pCanvas, SLOT(lockPolygon()));
    m_pMainWindowUI->verticalLayout->addWidget(button);
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
    m_pMainWindowUI->horizontalLayout->addWidget(m_pCanvas);
}

void MyMainWindow::AddDotToCanvas(QMouseEvent *event) {

}

void MyMainWindow::ConnectAllButtons() {
    //connect(m_pMainWindowUI->buttonDeleteLastAction_9, &QPushButton::clicked, m_pCanvas, &CanvasPolygon::clear);
    connect(m_pMainWindowUI->buttonAddLine, SIGNAL(clicked()), m_pCanvas, SLOT(pressedAddLineButton()));
    connect(m_pMainWindowUI->buttonRemoveLine, SIGNAL(clicked()), m_pCanvas, SLOT(pressedRemoveLineButton()));
    connect(m_pMainWindowUI->buttonUpdate, SIGNAL(clicked()), m_pCanvas, SLOT(pressedUpdatePolygonButton()));
}
