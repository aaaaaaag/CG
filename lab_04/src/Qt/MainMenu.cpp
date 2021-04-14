//
// Created by denis on 14.03.2021.
//

#include "Qt/MainMenu.h"
#include "QPushButton"
#include "QVBoxLayout"
#include "Qt/GraphicWidget.h"
#include "Qt/EntryLineCoords.h"
#include "Qt/DrawTypeComboBox.h"
#include "Qt/DrawColorComboBox.h"
#include "Qt/SpectreUI.h"
#include "QFormLayout"
#include "TimeManager.h"
#include "Qt/StairsGraphic.h"

#include "Qt/CirclePartUI.h"
#include "Qt/EllipsePartUI.h"
#include "Qt/CircleSpectrePartUI.h"
#include "Qt/EllipseSpectrePartUI.h"

MainMenu::MainMenu() {

    auto mainWindow = new QHBoxLayout;
    auto menu = new QVBoxLayout;

    auto typeBox = new DrawTypeComboBox;
    auto typeText = new QFormLayout();
    typeText->addRow("Выбор алгоритма", typeBox);
    auto colorBox = new DrawColorComboBox;
    auto colorText = new QFormLayout();
    colorText->addRow("Выбор цвета линии", colorBox);
    auto backgroundBox = new DrawColorComboBox;
    auto backgroundText = new QFormLayout();
    backgroundText->addRow("Выбор цвета фона", backgroundBox);
    backgroundBox->setCurrentIndex(4);

    auto circleData = new CirclePartUI;
    auto ellipseData = new EllipsePartUI;
    auto circleSpectreData = new CircleSpectrePartUI;
    auto ellipseSpectreData = new EllipseSpectrePartUI;

    auto spectreLayout = new SpectreUI;
    auto buttonAddCircle = new QPushButton;
    buttonAddCircle->setText("Draw circle");
    auto buttonAddEllipse = new QPushButton;
    buttonAddEllipse->setText("Draw ellipse");
    auto buttonClearCanvas = new QPushButton;
    buttonClearCanvas->setText("Clear");
    auto buttonDrawCircleSpectre = new QPushButton;
    buttonDrawCircleSpectre->setText("Draw circle spectre");
    auto buttonDrawEllipseSpectre = new QPushButton;
    buttonDrawEllipseSpectre->setText("Draw ellipse spectre");
    auto buttonDrawTimeCmp = new QPushButton;
    buttonDrawTimeCmp->setText("Time cmp");
    auto buttonGraphic = new QPushButton;
    buttonGraphic->setText("Stairs develop");


    auto graphicWidget = new GraphicWidget;
    auto timeGraph = new TimeManager(spectreLayout);
    timeGraph->ConnectButton(buttonDrawTimeCmp);
    auto stairsGraphic = new StairsGraphic;
    stairsGraphic->ConnectButton(buttonGraphic);

    graphicWidget->connectButtonToClearCanvas(buttonClearCanvas);

    graphicWidget->connectButtonToAddCircleFunc(buttonAddCircle, typeBox, colorBox, backgroundBox, circleData);
    graphicWidget->connectButtonToAddEllipseFunc(buttonAddEllipse, typeBox, colorBox, backgroundBox, ellipseData);
    graphicWidget->connectButtonToCircleSpectre(buttonDrawCircleSpectre, typeBox, colorBox, backgroundBox, circleSpectreData);
    graphicWidget->connectButtonToEllipseSpectre(buttonDrawEllipseSpectre, typeBox, colorBox, backgroundBox, ellipseSpectreData);


    menu->addLayout(typeText);
    menu->addLayout(colorText);
    menu->addLayout(backgroundText);

    menu->addLayout(circleData);
    menu->addWidget(buttonAddCircle);

    menu->addLayout(circleSpectreData);
    menu->addWidget(buttonDrawCircleSpectre);

    menu->addLayout(ellipseData);
    menu->addWidget(buttonAddEllipse);

    menu->addLayout(ellipseSpectreData);
    menu->addWidget(buttonDrawEllipseSpectre);

    menu->addWidget(buttonClearCanvas);
    menu->addWidget(buttonDrawTimeCmp);
    mainWindow->addLayout(menu);
    mainWindow->addWidget(graphicWidget);
    this->setLayout(mainWindow);
}
