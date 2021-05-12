//
// Created by denis on 18.04.2021.
//
#include <cmath>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <QtWidgets/QMessageBox>
#include "../inc/CanvasPolygon.h"
#include "QMouseEvent"
#include "../inc/MyMainWindow.h"
#include "QImage"
#include "QTimer"

void CanvasPolygon::myMousePressEvent(QMouseEvent *event) {
    currentMouseClick = event->pos();

    if (isAddLine)
    {
        currentLine.emplace_back(currentMouseClick.x(), currentMouseClick.y());
        if (currentLine.size() == 2) {
            DrawLine();
            currentLine.clear();
            isAddLine = false;
        }
    }
    else if (isUpdateRectangle)
    {
        m_pScene->clear();
        if (rectangleStartDot == dot_t(-1, -1)) {
            rectangleStartDot = dot_t(currentMouseClick.x(), currentMouseClick.y());
            for (auto line: m_vLines)
                DrawLineDDA(line.front(), line.back());
        }
        else
        {
            rectangleHeight = currentMouseClick.y() - rectangleStartDot.second;
            rectangleWidth = currentMouseClick.x() - rectangleStartDot.first;
            drawRectangle();
            for (auto line: m_vLines)
                DrawLineDDA(line.front(), line.back());
            isUpdateRectangle = false;
        }
    }
}

CanvasPolygon::CanvasPolygon(Ui::MainWindow *ui) {

    m_pScene = new QGraphicsScene;
    ResizeCanvas(600, 600);
    this->setScene(m_pScene);
    this->setSceneRect(0, 0, 600, 600);
    m_pPen = new QPen;
    m_pUi = ui;
    isCtrl = false;
    isAddLine = false;
    isUpdateRectangle = false;

    rectangleStartDot = dot_t(250, 250);
    rectangleHeight = 100;
    rectangleWidth = 200;
    drawRectangle();

    connect(this, SIGNAL(pressedMouse(QMouseEvent *)), this, SLOT(myMousePressEvent(QMouseEvent *)));
}

void CanvasPolygon::DrawLine() {
    if (!currentLine.empty()) {
        if (!isCtrl) {
            m_vLines.push_back(currentLine);
            DrawLineDDA(currentLine.front(), currentLine.back());
        }
        else
        {
            line_t resLine;
            resLine.push_back(currentLine.front());
            auto dx = abs(currentLine.back().first - currentLine.front().first);
            auto dy = abs(currentLine.back().second - currentLine.front().second);
            if (dx > dy) {
                DrawLineDDA(currentLine.front(), dot_t(currentLine.back().first, currentLine.front().second));
                resLine.emplace_back(dot_t(currentLine.back().first, currentLine.front().second));
            }
            else {
                DrawLineDDA(currentLine.front(), dot_t(currentLine.front().first, currentLine.back().second));
                resLine.emplace_back(dot_t(currentLine.front().first, currentLine.back().second));
            }
            m_vLines.push_back(resLine);
        }
    }
}

void CanvasPolygon::mousePressEvent(QMouseEvent *event) {
    emit pressedMouse(event);
}

void CanvasPolygon::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Control)
        isCtrl = true;
}

void CanvasPolygon::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Control)
        isCtrl = false;
}

void CanvasPolygon::ResizeCanvas(int w, int h) {
    this->setMaximumSize(w, h);
    this->setMinimumSize(w, h);
}

void drawPixel(dot_t pixel, QGraphicsScene *scene, const QPen& pen)
{
    scene->addLine(pixel.first, pixel.second, pixel.first, pixel.second, pen);
}

void CanvasPolygon::DrawLineDDA(dot_t from, dot_t to) {
    double x1 = from.first, x2 = to.first, y1 = from.second, y2 = to.second, length;

    m_pPen->setColor(QColor(0, 255, 0));

    auto dx = x2 - x1;
    auto dy = y2 - y1;

    if (abs(dx) - abs(dy) >= 0) length = abs(dx);
    else length = abs(dy);

    dx /= length; dy /= length;
    auto x = x1, y = y1;

    bool isInside = false;

    for (int i = 0; i < length + 1; i++)
    {
        if (y > rectangleStartDot.second && y < rectangleStartDot.second + rectangleHeight &&
        x > rectangleStartDot.first && x < rectangleStartDot.first + rectangleWidth && !isInside)
        {
            isInside = true;
            m_pPen->setColor(QColor(0, 0, 255));
        }
        if ((y <= rectangleStartDot.second || y >= rectangleStartDot.second + rectangleHeight ||
            x <= rectangleStartDot.first || x >= rectangleStartDot.first + rectangleWidth) && isInside)
        {
            isInside = false;
            m_pPen->setColor(QColor(0, 255, 0));
        }
        drawPixel(dot_t(x, y), m_pScene, *m_pPen);
        x += dx; y += dy;
    }
}

void CanvasPolygon::pressedAddLineButton() {
    if (isUpdateRectangle)
        QMessageBox::critical(this, "Ошибка ", "Сначала задайте новый прямоугольник", QMessageBox::Ok);
    else if (isAddLine)
        QMessageBox::critical(this, "Ошибка ", "Процесс добавления линии уже запущен", QMessageBox::Ok);
    else
        isAddLine = true;
}

void CanvasPolygon::pressedRemoveLineButton() {
    if (isAddLine || isUpdateRectangle)
        QMessageBox::critical(this, "Ошибка ", "Прежде завершите запущенные процессы", QMessageBox::Ok);
    else
    {
        m_pScene->clear();
        m_vLines.clear();
        drawRectangle();
    }
}

void CanvasPolygon::pressedUpdateRectangleButton() {
    if (isAddLine)
        QMessageBox::critical(this, "Ошибка ", "Сначала добавьте новую линию", QMessageBox::Ok);
    else if (isUpdateRectangle)
        QMessageBox::critical(this, "Ошибка ", "Процесс обновления отсекателя уже запущен", QMessageBox::Ok);
    else {
        isUpdateRectangle = true;
        rectangleStartDot = dot_t(-1, -1);
        m_pScene->clear();
        for (auto line: m_vLines)
            DrawLineDDA(line.front(), line.back());
    }
}

void CanvasPolygon::drawRectangle() {
    QPointF start(rectangleStartDot.first, rectangleStartDot.second);
    QSizeF size(rectangleWidth, rectangleHeight);
    m_pPen->setColor(QColor(255, 0, 0));
    m_pScene->addRect(QRectF(start, size), *m_pPen);
}
