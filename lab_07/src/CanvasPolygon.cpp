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
            isAddLine = false;
            auto cutLine = cut(currentLine.front(), currentLine.back());

            currentLine.clear();
            if (!cutLine.empty())
            {
                m_pPen->setColor(QColor(0, 0, 255));
                m_pScene->addLine(cutLine.front().first, cutLine.front().second,
                                  cutLine.back().first, cutLine.back().second, *m_pPen);
            }
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
            for (auto line: m_vLines) {
                DrawLineDDA(line.front(), line.back());
                auto cutLine = cut(line.front(), line.back());
                if (!cutLine.empty())
                {
                    m_pPen->setColor(QColor(0, 0, 255));
                    m_pScene->addLine(cutLine.front().first, cutLine.front().second,
                                      cutLine.back().first, cutLine.back().second, *m_pPen);
                }
            }
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
            currentLine = resLine;
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
    m_pScene->addLine(x1, y1, x2, y2, *m_pPen);
//    auto dx = x2 - x1;
//    auto dy = y2 - y1;
//
//    if (abs(dx) - abs(dy) >= 0) length = abs(dx);
//    else length = abs(dy);
//
//    dx /= length; dy /= length;
//    auto x = x1, y = y1;
//
//    bool isInside = false;
//
//    for (int i = 0; i < length + 1; i++)
//    {
//        if (y > rectangleStartDot.second && y < rectangleStartDot.second + rectangleHeight &&
//        x > rectangleStartDot.first && x < rectangleStartDot.first + rectangleWidth && !isInside)
//        {
//            isInside = true;
//            m_pPen->setColor(QColor(0, 0, 255));
//        }
//        if ((y <= rectangleStartDot.second || y >= rectangleStartDot.second + rectangleHeight ||
//            x <= rectangleStartDot.first || x >= rectangleStartDot.first + rectangleWidth) && isInside)
//        {
//            isInside = false;
//            m_pPen->setColor(QColor(0, 255, 0));
//        }
//        drawPixel(dot_t(x, y), m_pScene, *m_pPen);
//        x += dx; y += dy;
//    }
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

line_t CanvasPolygon::cut(dot_t p1, dot_t p2) {
    float m = 0;
    float Im = 0;
    float dx = p2.first - p1.first;
    float dy = p2.second - p1.second;
    bool isVert = ((p2.first - p1.first) == 0);
    bool isHor = ((p2.second - p1.second) == 0);
    if (!isVert)
        m = dy / dx;

    if (!isHor)
        Im = dx / dy;

    Rectangle rectangle(rectangleStartDot, rectangleWidth, rectangleHeight);

    unsigned int mask = 0b1000u; // для обращения к i-ому разряду кода вершины
    for (int i = 0; i < 4; i++)
    {
        unsigned int t0 = rectangle.getCode(p1);
        unsigned int t1 = rectangle.getCode(p2);

        if (Rectangle::isLineVisible(t0, t1))
            return line_t{p1, p2};
        if (Rectangle::isTrivialInvisible(t0, t1))
            return line_t();

        bool t0i = ((t0 & mask) != 0);
        bool t1i = ((t1 & mask) != 0);

        // если t0i или t1i равен единице.
        if (t0i != t1i)
        {
            if (!t0i) // Если точка P1 по видимую сторону, поменять местами вершины
                std::swap(p1, p2);

            if (!isVert && i < 2)
            {
                p1.second = m * (rectangle.getCoord(i) - p1.first) + p1.second;
                p1.first = rectangle.getCoord(i);
            }
            else
            {
                if (!isHor)
                {
                    p1.first = Im * (rectangle.getCoord(i) - p1.second) + p1.first;
                    p1.second = rectangle.getCoord(i);
                }
            }
        }
        mask /= 2;
    }
    return line_t {p1, p2};
}
