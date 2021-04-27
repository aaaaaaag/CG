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
    this->setMaximumSize(600, 600);
    this->setMinimumSize(600, 600);
    mScene->setSceneRect(0, 0, 600, 600);
}

void GraphicWidget::connectButtonToClearCanvas(QPushButton* button) const {

    connect(button, &QPushButton::clicked, this, &GraphicWidget::Clear);
}

void GraphicWidget::connectButtonToAddCircleFunc(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                                 IDrawColorGetter *boxDrawColor, IDrawColorGetter *backgroundColor,
                                                 ICircleInformationGetter *dataLayout) {
    m_pCircleDataGetter = dataLayout;
    m_pDrawTypeGetter = boxDrawType;
    m_pDrawColorGetter = boxDrawColor;
    m_pBackgroundColorGetter = backgroundColor;
    connect(button, &QPushButton::clicked, this, &GraphicWidget::addCircle);
}

void GraphicWidget::connectButtonToAddEllipseFunc(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                                  IDrawColorGetter *boxDrawColor, IDrawColorGetter *backgroundColor,
                                                  IEllipseInformationGetter *dataLayout) {
    m_pEllipseDataGetter = dataLayout;
    m_pDrawTypeGetter = boxDrawType;
    m_pDrawColorGetter = boxDrawColor;
    m_pBackgroundColorGetter = backgroundColor;
    connect(button, &QPushButton::clicked, this, &GraphicWidget::addEllipse);
}

void GraphicWidget::connectButtonToCircleSpectre(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                                 IDrawColorGetter *boxDrawColor, IDrawColorGetter *backgroundColor,
                                                 ICircleSpectreInformationGetter *dataGetter) {
    m_pCircleSpectreDataGetter = dataGetter;
    m_pDrawTypeGetter = boxDrawType;
    m_pDrawColorGetter = boxDrawColor;
    m_pBackgroundColorGetter = backgroundColor;
    connect(button, &QPushButton::clicked, this, &GraphicWidget::drawCircleSpectre);
}

void GraphicWidget::connectButtonToEllipseSpectre(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                                  IDrawColorGetter *boxDrawColor, IDrawColorGetter *backgroundColor,
                                                  IEllipseSpectreInformationGetter *dataGetter) {
    m_pEllipseSpectreDataGetter = dataGetter;
    m_pDrawTypeGetter = boxDrawType;
    m_pDrawColorGetter = boxDrawColor;
    m_pBackgroundColorGetter = backgroundColor;
    connect(button, &QPushButton::clicked, this, &GraphicWidget::drawEllipseSpectre);
}

void GraphicWidget::Clear() {
    mScene->clear();
}

void GraphicWidget::addCircle() {
    dot center;
    double radius;
    if (!m_pCircleDataGetter->GetCenter(center) || !m_pCircleDataGetter->GetRadius(radius))
    {
        QMessageBox::critical(this, "Ошибка ", "Неверный ввод координат.", QMessageBox::Ok);
        return;
    }
    setBackgroundBrush(QBrush(DrawLine::getColorByType(m_pBackgroundColorGetter->GetDrawColor()), Qt::SolidPattern));
    DrawLine::drawCircle(m_pDrawTypeGetter->GetSelectedMode(), m_pDrawColorGetter->GetDrawColor(), center, radius, mScene);
}

void GraphicWidget::addEllipse() {
    dot center;
    double xAxis, yAxis;
    if (!m_pEllipseDataGetter->GetCenter(center) || !m_pEllipseDataGetter->GetXAxisLen(xAxis) || !m_pEllipseDataGetter->GetYAxisLen(yAxis))
    {
        QMessageBox::critical(this, "Ошибка ", "Неверный ввод координат.", QMessageBox::Ok);
        return;
    }
    setBackgroundBrush(QBrush(DrawLine::getColorByType(m_pBackgroundColorGetter->GetDrawColor()), Qt::SolidPattern));
    DrawLine::drawEllipse(m_pDrawTypeGetter->GetSelectedMode(), m_pDrawColorGetter->GetDrawColor(), center, xAxis, yAxis, mScene);
}

void GraphicWidget::drawCircleSpectre() {
    auto getter = m_pCircleSpectreDataGetter;
    std::vector<double> vData;
    vData.reserve(4);
    std::vector<bool> vErr;

    vErr.push_back(getter->GetStartRadius(vData[0]));
    vErr.push_back(getter->GetEndRadius(vData[1]));
    vErr.push_back(getter->GetRadiusStep(vData[2]));
    vErr.push_back(getter->GetCircleNumb(vData[3]));

    int totalErr = 0;
    for (auto err: vErr)
    {
        if (err)
            totalErr++;
    }

    if (totalErr != 3)
    {
        QMessageBox::critical(this, "Ошибка ", "Неверное количество параметров", QMessageBox::Ok);
        return;
    }

    dot center;
    if (!m_pCircleDataGetter->GetCenter(center))
    {
        QMessageBox::critical(this, "Ошибка ", "Неверный ввод координат.", QMessageBox::Ok);
        return;
    }

    if (!vErr[0])
    {
        setBackgroundBrush(QBrush(DrawLine::getColorByType(m_pBackgroundColorGetter->GetDrawColor()), Qt::SolidPattern));
        double startRadius = vData[1] - vData[2] * vData[3];
        for (int i = 0; i <= vData[3]; i++) {
            DrawLine::drawCircle(m_pDrawTypeGetter->GetSelectedMode(), m_pDrawColorGetter->GetDrawColor(), center,
                                 startRadius, mScene);
            startRadius += vData[2];
        }
    }
    else if (!vErr[1])
    {
        setBackgroundBrush(QBrush(DrawLine::getColorByType(m_pBackgroundColorGetter->GetDrawColor()), Qt::SolidPattern));
        double startRadius = vData[0];
        for (int i = 0; i <= vData[3]; i++) {
            DrawLine::drawCircle(m_pDrawTypeGetter->GetSelectedMode(), m_pDrawColorGetter->GetDrawColor(), center,
                                 startRadius, mScene);
            startRadius += vData[2];
        }
    }
    else if (!vErr[2])
    {
        setBackgroundBrush(QBrush(DrawLine::getColorByType(m_pBackgroundColorGetter->GetDrawColor()), Qt::SolidPattern));
        double startRadius = vData[0];
        double delta = (vData[1] - startRadius) / vData[3];
        for (int i = 0; i <= vData[3]; i++) {
            DrawLine::drawCircle(m_pDrawTypeGetter->GetSelectedMode(), m_pDrawColorGetter->GetDrawColor(), center,
                                 startRadius, mScene);
            startRadius += delta;
        }
    }
    else if (!vErr[3])
    {
        setBackgroundBrush(QBrush(DrawLine::getColorByType(m_pBackgroundColorGetter->GetDrawColor()), Qt::SolidPattern));
        int numb = static_cast<int>((vData[1] - vData[0]) / vData[2]);
        double startRadius = vData[0];
        for (int i = 0; i <= numb; i++) {
            DrawLine::drawCircle(m_pDrawTypeGetter->GetSelectedMode(), m_pDrawColorGetter->GetDrawColor(), center,
                                 startRadius, mScene);
            startRadius += vData[2];
        }
    }
}

void GraphicWidget::drawEllipseSpectre() {
    double ellipseNumb, axisStep;
    if (!m_pEllipseSpectreDataGetter->GetAxisStep(axisStep) || !m_pEllipseSpectreDataGetter->GetEllipseNumb(ellipseNumb))
    {
        QMessageBox::critical(this, "Ошибка ", "Неверный ввод координат.", QMessageBox::Ok);
        return;
    }

    dot center;
    double xAxis, yAxis;
    if (!m_pEllipseDataGetter->GetCenter(center) || !m_pEllipseDataGetter->GetXAxisLen(xAxis) || !m_pEllipseDataGetter->GetYAxisLen(yAxis))
    {
        QMessageBox::critical(this, "Ошибка ", "Неверный ввод координат.", QMessageBox::Ok);
        return;
    }
    setBackgroundBrush(QBrush(DrawLine::getColorByType(m_pBackgroundColorGetter->GetDrawColor()), Qt::SolidPattern));
    for (int i = 0; i < ellipseNumb; i++)
    {
        DrawLine::drawEllipse(m_pDrawTypeGetter->GetSelectedMode(), m_pDrawColorGetter->GetDrawColor(), center, xAxis, yAxis, mScene);
        xAxis *= axisStep;
        yAxis *= axisStep;
    }
}













