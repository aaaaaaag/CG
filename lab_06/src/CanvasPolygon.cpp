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

QColor getColorByType(const std::string& color) {
    if (color == "Белый")
        return QColor(255, 255, 255);
    else if (color == "Чёрный")
        return QColor(0, 0, 0);
    else if (color == "Красный")
        return QColor(255, 0, 0);
    else if (color == "Зелёный")
        return QColor(0, 255, 0);
    else if (color == "Синий")
        return QColor(0, 0, 255);
    else if (color == "Жёлтый")
        return QColor(255, 255, 0);
    else
        return QColor(0, 0, 0);
}

void CanvasPolygon::myMousePressEvent(QMouseEvent *event) {
    currentMouseClick = event->pos();
    if (!isTrav)
        DrawLine();
    else {
        if (isMouseInFigure()) {
            Fill();
            isTrav = false;
        }
        else
        {
            QMessageBox::critical(this, "Ошибка ", "Точка затравки не лежит внутри фигуры. Введите ее снова", QMessageBox::Ok);
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
    connect(this, SIGNAL(pressedMouse(QMouseEvent *)), this, SLOT(myMousePressEvent(QMouseEvent *)));

    isTrav = false;
    minX = 0;
    maxX = 0;
    centerX = 0;
}

void CanvasPolygon::DrawLine() {

    m_pPen->setColor(getColorByType(m_pUi->comboBoxColor_9->currentText().toStdString()));
    if (!m_vPolygonDots.empty()) {

        if (currentMouseClick.x() > maxX)
            maxX = currentMouseClick.x();
        if (currentMouseClick.x() < minX)
            minX = currentMouseClick.x();

        
        if (!isCtrl) {
            DrawLineDDA(dot_t(m_vPolygonDots.back().x(), m_vPolygonDots.back().y()), dot_t(currentMouseClick.x(), currentMouseClick.y()));
            //m_pScene->addLine(QLineF(m_vPolygonDots.back(), currentMouseClick), *m_pPen);
            m_vPolygonDots.push_back(currentMouseClick);
        }
        else
        {
            auto dx = abs(m_vPolygonDots.back().x() - currentMouseClick.x());
            auto dy = abs(m_vPolygonDots.back().y() - currentMouseClick.y());
            if (dx > dy) {
                DrawLineDDA(dot_t(m_vPolygonDots.back().x(), m_vPolygonDots.back().y()), dot_t(currentMouseClick.x(), m_vPolygonDots.back().y()));
                //m_pScene->addLine(QLineF(m_vPolygonDots.back(),
                   //                      QPointF(currentMouseClick.x(), m_vPolygonDots.back().y())), *m_pPen);
                m_vPolygonDots.emplace_back(currentMouseClick.x(), m_vPolygonDots.back().y());
            }
            else {
                DrawLineDDA(dot_t(m_vPolygonDots.back().x(), m_vPolygonDots.back().y()), dot_t(m_vPolygonDots.back().x(), currentMouseClick.y()));
               // m_pScene->addLine(QLineF(m_vPolygonDots.back(),
                     //                    QPointF(m_vPolygonDots.back().x(), currentMouseClick.y())), *m_pPen);
                m_vPolygonDots.emplace_back(m_vPolygonDots.back().x(), currentMouseClick.y());
            }
        }
    }
    else {
        m_vPolygonDots.push_back(currentMouseClick);
        minX = currentMouseClick.x();
        maxX = minX;
    }
}

void CanvasPolygon::mousePressEvent(QMouseEvent *event) {
    emit pressedMouse(event);
}

void CanvasPolygon::Clear() {
    m_pScene->clear();
    for (auto & i : m_vPixColorMap)
    {
        for (auto & j : i)
            j = QColor(255, 255, 255);
    }
    m_vLines.clear();
    m_vPolygonDots.clear();
}

void CanvasPolygon::DeleteLastDot() {
    Clear();
    if (!m_vPolygonDots.empty()) {
        m_vPolygonDots.pop_back();
        for (auto dot: m_vLines.back())
        {
            m_vPixColorMap[dot.first][dot.second] = QColor(255, 255, 255);
        }
        m_vLines.pop_back();
    }
    for (int i = 0; i < m_vPolygonDots.size() - 1; i++)
        m_pScene->addLine(QLineF(m_vPolygonDots[i], m_vPolygonDots[i + 1]), *m_pPen);


}

void CanvasPolygon::LockAndFill() {
    m_pPen->setColor(getColorByType(m_pUi->comboBoxColor_9->currentText().toStdString()));
    if (m_vPolygonDots.size() > 2)
        DrawLineDDA(dot_t(m_vPolygonDots.back().x(), m_vPolygonDots.back().y()), dot_t(m_vPolygonDots.front().x(), m_vPolygonDots.front().y()));
        //m_pScene->addLine(QLineF(m_vPolygonDots.front(), m_vPolygonDots.back()), *m_pPen);
    isTrav = true;
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

    CreatePixColorMap(w, h);
}

void CanvasPolygon::CreatePixColorMap(int w, int h) {
    m_vPixColorMap.clear();
    for (int i = 0; i < h; i++)
    {
        std::vector<QColor> vColor;
        vColor.reserve(w);
        for (int j = 0; j < w; j++)
            vColor.emplace_back(255, 255, 255);
        m_vPixColorMap.push_back(vColor);
    }
}

void drawPixel(dot_t pixel, QGraphicsScene *scene, const QPen& pen)
{
    scene->addLine(pixel.first, pixel.second, pixel.first, pixel.second, pen);
}

void CanvasPolygon::DrawLineDDA(dot_t from, dot_t to) {
    m_pPen->setColor(getColorByType(m_pUi->comboBoxColor_9->currentText().toStdString()));
    double x1 = from.first, x2 = to.first, y1 = from.second, y2 = to.second, length;

    auto dx = x2 - x1;
    auto dy = y2 - y1;

    if (abs(dx) - abs(dy) >= 0) length = abs(dx);
    else length = abs(dy);

    dx /= length; dy /= length;
    auto x = x1, y = y1;

    int prevX, prevY;
    int stairsNumb = 0;
    line_t resLine;
    for (int i = 0; i < length + 1; i++)
    {
        prevX = x;
        prevY = y;
        drawPixel(dot_t(x, y), m_pScene, *m_pPen);
        resLine.emplace_back(x, y);
        m_vPixColorMap[(int)x][(int)y] = m_pPen->color();
        x += dx; y += dy;
        if (prevX == static_cast<int>(x) - 1 && prevY == static_cast<int>(y) - 1)
            stairsNumb++;
    }
    if (resLine.back() != to)
        resLine.back() = to;
    if (resLine.front() != from)
        resLine.front() = from;
    m_vLines.push_back(resLine);
}


QColor GetNegColor(const QColor& color)
{
    return QColor(255 - color.red(), 255 - color.green(), 255 - color.blue());
}



void CanvasPolygon::Fill() {
    m_vPixColorMapOld = m_vPixColorMap;
    auto fillColor = getColorByType(m_pUi->comboBoxColor_9->currentText().toStdString());
    m_pPen->setColor(fillColor);

    m_vStack.emplace_back(currentMouseClick.x(), currentMouseClick.y());
    while(!m_vStack.empty())
    {
        if (m_pUi->comboBoxDelay_9->currentIndex() == 0 && m_vStack.size() % 128 == 0) {
            QApplication::processEvents(QEventLoop::AllEvents);
        }
        auto pix = m_vStack.back();
        m_vStack.pop_back();

        drawPixel(dot_t(pix.first, pix.second), m_pScene, *m_pPen);
        m_vPixColorMap[pix.first][pix.second] = fillColor;
        if (m_vPixColorMap[pix.first - 1][pix.second] != fillColor)
            m_vStack.emplace_back(pix.first - 1, pix.second);
        if (m_vPixColorMap[pix.first][pix.second + 1] != fillColor)
            m_vStack.emplace_back(pix.first, pix.second + 1);
        if (m_vPixColorMap[pix.first + 1][pix.second] != fillColor)
            m_vStack.emplace_back(pix.first + 1, pix.second);
        if (m_vPixColorMap[pix.first][pix.second - 1] != fillColor)
            m_vStack.emplace_back(pix.first, pix.second - 1);

    }
    m_vLines.clear();
    m_vPolygonDots.clear();
}

bool CanvasPolygon::isMouseInFigure() {
    auto pos = currentMouseClick;
    auto fillColor = getColorByType(m_pUi->comboBoxColor_9->currentText().toStdString());
    auto posX = pos.x();
    while (posX < m_pScene->width())
    {
        if (m_vPixColorMap[posX][pos.y()] == fillColor)
            break;
        posX++;
    }
    if (posX == m_pScene->width())
        return false;

    posX = pos.x();
    while (posX > 0)
    {
        if (m_vPixColorMap[posX][pos.y()] == fillColor)
            break;
        posX--;
    }
    if (posX == 0)
        return false;

    auto posY = pos.y();
    while (posY < m_pScene->height())
    {
        if (m_vPixColorMap[pos.x()][posY] == fillColor)
            break;
        posY++;
    }
    if (posY == m_pScene->height())
        return false;

    posY = pos.y();
    while (posY > 0)
    {
        if (m_vPixColorMap[pos.x()][posY] == fillColor)
            break;
        posY--;
    }
    if (posY == 0)
        return false;

    return true;
}
