//
// Created by denis on 14.03.2021.
//

#include <QtWidgets/QMessageBox>
#include <cmath>
#include "Qt/GraphicWidget.h"
#include "DrawLine.h"

GraphicWidget::GraphicWidget() {
    mScene = new QGraphicsScene;
    this->setScene(mScene);
    this->setMaximumSize(400, 400);
    this->setMinimumSize(400, 400);
}

void GraphicWidget::connectButtonToClearCanvas(QPushButton* button) const {

    connect(button, &QPushButton::clicked, this, &GraphicWidget::Clear);
}

void GraphicWidget::connectButtonToAddLineFunc(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                               IDrawColorGetter *boxDrawColor, IDrawColorGetter* backgroundColor,
                                               ICoordsGetter *dataLayout) {
    m_pDrawDataGetter = dataLayout;
    m_pDrawTypeGetter = boxDrawType;
    m_pDrawColorGetter = boxDrawColor;
    m_pBackgroundColorGetter = backgroundColor;
    connect(button, &QPushButton::clicked, this, &GraphicWidget::AddLine);
}

void GraphicWidget::connectButtonToDrawSpectreFunc(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                                   IDrawColorGetter *boxDrawColor, IDrawColorGetter* backgroundColor,
                                                   ISpectreInformationGetter *dataGetter) {
    m_pSpecterDataGetter = dataGetter;
    m_pDrawTypeGetter = boxDrawType;
    m_pDrawColorGetter = boxDrawColor;
    m_pBackgroundColorGetter = backgroundColor;
    connect(button, &QPushButton::clicked, this, &GraphicWidget::DrawSpectre);
}

void GraphicWidget::Clear() {
    mScene->clear();
}

void GraphicWidget::AddLine() {
    dot startCoord, endCoord;
    if (!m_pDrawDataGetter->GetStartCoord(startCoord) || !m_pDrawDataGetter->GetEndCoord(endCoord)) {
        QMessageBox::critical(this, "Ошибка ", "Неверный ввод координат.", QMessageBox::Ok);
        return;
    }
    setBackgroundBrush(QBrush(DrawLine::getColorByType(m_pBackgroundColorGetter->GetDrawColor()), Qt::SolidPattern));
    DrawLine::drawLine(m_pDrawTypeGetter->GetSelectedMode(), m_pDrawColorGetter->GetDrawColor(), startCoord, endCoord, mScene);
}

void GraphicWidget::DrawSpectre() {
    double degrees, cutLength;
    if (!m_pSpecterDataGetter->GetDegrees(degrees) || !m_pSpecterDataGetter->GetLineLength(cutLength)) {
        QMessageBox::critical(this, "Ошибка ", "Неверный ввод данных для составления спектра.", QMessageBox::Ok);
        return;
    }
    for (int i = 0; i < 360; i += degrees)
    {
        double rad = i * M_PI / 180;
        double x = cutLength * cos(rad);
        double y = cutLength * sin(rad);
        setBackgroundBrush(QBrush(DrawLine::getColorByType(m_pBackgroundColorGetter->GetDrawColor()), Qt::SolidPattern));
        DrawLine::drawLine(m_pDrawTypeGetter->GetSelectedMode(), m_pDrawColorGetter->GetDrawColor(), dot(0, 0), dot(x, y), mScene);
    }
}






