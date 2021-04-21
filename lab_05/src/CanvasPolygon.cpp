//
// Created by denis on 18.04.2021.
//
#include <cmath>
#include <iostream>
#include <unistd.h>
#include <thread>
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
    DrawLine();
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
    Fill();
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
//    for (const auto& line: m_vPixColorMap)
//    {
//        for (const auto& d: line)
//        {
//            if (d == QColor(255, 255, 255))
//                std::cout << "0 ";
//            else
//                std::cout << "1 ";
//        }
//        std::cout << std::endl;
//    }
    centerX = minX + (maxX - minX) / 2;

    //std::cout << (QColor(255, 255, 255) == QColor(255, 255, 255)) << std::endl;
    m_vPixColorMapOld = m_vPixColorMap;
    auto fillColor = getColorByType(m_pUi->comboBoxColor_9->currentText().toStdString());
    m_pPen->setColor(fillColor);
    //m_pScene->addLine(centerX, 0, centerX, 600, *m_pPen);
    for (const auto& line: m_vLines)
    {
        bool direction;
        if (line.front().first > line.back().first)
            direction = false;
        else
            direction = true;

        for (int i = 1; i < line.size(); i++)
        {
            //std::this_thread::sleep_for(std::chrono::seconds(3));
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
            auto dot = line[i];
            if (m_pUi->comboBoxDelay_9->currentIndex() == 0)
                QApplication::processEvents(QEventLoop::AllEvents);
            if (dot.first < centerX)
            {
                if ((direction && dot.second == line[i + 1].second) || (!direction && dot.second == line[i - 1].second))
                    continue;
                for (int x = dot.first; x < centerX; x++)
                {
                    if (m_vPixColorMap[x][dot.second] != fillColor)
                    {
                        m_pPen->setColor(fillColor);
                        drawPixel(dot_t(x, dot.second), m_pScene, *m_pPen);
                        m_vPixColorMap[x][dot.second] = fillColor;
                    }
                    else
                    {
                        m_pPen->setColor(m_vPixColorMapOld[x][dot.second]);
                        drawPixel(dot_t(x, dot.second), m_pScene, *m_pPen);
                        m_vPixColorMap[x][dot.second] = m_vPixColorMapOld[x][dot.second];
                    }
                }
            }
            else if (dot.first > centerX)
            {
                if ((!direction && dot.second == line[i + 1].second) || (direction && dot.second == line[i - 1].second))
                    continue;
                for (int x = dot.first; x >= centerX; x--)
                {
                    if (m_vPixColorMap[x][dot.second] != fillColor)
                    {
                        m_pPen->setColor(fillColor);
                        drawPixel(dot_t(x, dot.second), m_pScene, *m_pPen);
                        m_vPixColorMap[x][dot.second] = fillColor;
                    }
                    else
                    {
                        m_pPen->setColor(m_vPixColorMapOld[x][dot.second]);
                        drawPixel(dot_t(x, dot.second), m_pScene, *m_pPen);
                        m_vPixColorMap[x][dot.second] = m_vPixColorMapOld[x][dot.second];
                    }
                }
            }
        }
    }
    m_vLines.clear();
    m_vPolygonDots.clear();
}
