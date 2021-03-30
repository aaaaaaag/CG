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

    auto linesLayout = new EntryLineCoords;
    auto spectreLayout = new SpectreUI;
    auto buttonAddLine = new QPushButton;
    buttonAddLine->setText("Draw");
    auto buttonClearCanvas = new QPushButton;
    buttonClearCanvas->setText("Clear");
    auto buttonDrawSpectre = new QPushButton;
    buttonDrawSpectre->setText("Draw spectre");
    auto buttonDrawTimeCmp = new QPushButton;
    buttonDrawTimeCmp->setText("Time cmp");
    auto buttonGraphic = new QPushButton;
    buttonGraphic->setText("Stairs develop");


    auto graphicWidget = new GraphicWidget;
    auto timeGraph = new TimeManager(spectreLayout);
    timeGraph->ConnectButton(buttonDrawTimeCmp);
    auto stairsGraphic = new StairsGraphic;
    stairsGraphic->ConnectButton(buttonGraphic);
    graphicWidget->connectButtonToAddLineFunc(buttonAddLine, typeBox, colorBox, backgroundBox, linesLayout);
    graphicWidget->connectButtonToClearCanvas(buttonClearCanvas);
    graphicWidget->connectButtonToDrawSpectreFunc(buttonDrawSpectre, typeBox, colorBox, backgroundBox, spectreLayout);

    menu->addLayout(typeText);
    menu->addLayout(colorText);
    menu->addLayout(backgroundText);
    menu->addLayout(linesLayout);
    menu->addWidget(buttonAddLine);
    menu->addLayout(spectreLayout);
    menu->addWidget(buttonDrawSpectre);
    menu->addWidget(buttonClearCanvas);
    menu->addWidget(buttonDrawTimeCmp);
    menu->addWidget(buttonGraphic);
    mainWindow->addLayout(menu);
    mainWindow->addWidget(graphicWidget);
    this->setLayout(mainWindow);
}
