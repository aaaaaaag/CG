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
            DrawLine(currentLine.front(), currentLine.back());
            isAddLine = false;
            if (!vPolygonDots.empty())
            {
                auto cuttedLine = cutLine(currentLine.front(), currentLine.back());
                m_pPen->setColor(QColor(0, 0, 255));
                if (!cuttedLine.empty())
                    DrawLineDDA(cuttedLine.front(), cuttedLine.back());
            }
            currentLine.clear();
        }
    }
    else if (isUpdateShape)
    {
        if (!vPolygonDots.empty())
            DrawLine(vPolygonDots.back(), dot_t(currentMouseClick.x(), currentMouseClick.y()));
        else
            vPolygonDots.emplace_back(currentMouseClick.x(), currentMouseClick.y());
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
    isUpdateShape = false;

    connect(this, SIGNAL(pressedMouse(QMouseEvent *)), this, SLOT(myMousePressEvent(QMouseEvent *)));
}

void CanvasPolygon::DrawLine(dot_t A, dot_t B) {

    if (!isCtrl) {
        if (isAddLine)
            m_vLines.push_back(currentLine);
        if (isUpdateShape)
            vPolygonDots.push_back(B);
        DrawLineDDA(A, B);
    }
    else
    {
        line_t resLine;
        resLine.push_back(A);
        auto dx = abs(B.first - A.first);
        auto dy = abs(B.second - A.second);
        if (dx > dy) {
            DrawLineDDA(A, dot_t(B.first, A.second));
            if (isUpdateShape)
                vPolygonDots.emplace_back(B.first, A.second);
            resLine.emplace_back(dot_t(B.first, A.second));
        }
        else {
            DrawLineDDA(A, dot_t(A.first, B.second));
            if (isUpdateShape)
                vPolygonDots.emplace_back(A.first, B.second);
            resLine.emplace_back(dot_t(A.first, B.second));
        }
        if (isAddLine) {
            currentLine = resLine;
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

    if (isAddLine)
        m_pPen->setColor(QColor(0, 255, 0));
    else if (isUpdateShape)
        m_pPen->setColor(QColor(255, 0, 0));

    m_pScene->addLine(from.first, from.second, to.first, to.second, *m_pPen);

//    auto dx = x2 - x1;
//    auto dy = y2 - y1;
//
//    if (abs(dx) - abs(dy) >= 0) length = abs(dx);
//    else length = abs(dy);
//
//    dx /= length; dy /= length;
//    auto x = x1, y = y1;
//
//    for (int i = 0; i < length + 1; i++)
//    {
//        drawPixel(dot_t(x, y), m_pScene, *m_pPen);
//        x += dx; y += dy;
//    }
}

void CanvasPolygon::pressedAddLineButton() {
    if (isUpdateShape)
        QMessageBox::critical(this, "Ошибка ", "Сначала задайте новый прямоугольник", QMessageBox::Ok);
    else if (isAddLine)
        QMessageBox::critical(this, "Ошибка ", "Процесс добавления линии уже запущен", QMessageBox::Ok);
    else
        isAddLine = true;
}

void CanvasPolygon::pressedRemoveLineButton() {
    if (isAddLine || isUpdateShape)
        QMessageBox::critical(this, "Ошибка ", "Прежде завершите запущенные процессы", QMessageBox::Ok);
    else
    {
        m_pScene->clear();
        m_vLines.clear();
        m_pPen->setColor(QColor(255, 0, 0));
        for (size_t i = 0; i < vPolygonDots.size(); i++)
            DrawLineDDA(vPolygonDots[i], vPolygonDots[(i + 1) % vPolygonDots.size()]);
    }
}

void CanvasPolygon::pressedUpdatePolygonButton() {
    if (isAddLine)
        QMessageBox::critical(this, "Ошибка ", "Сначала добавьте новую линию", QMessageBox::Ok);
    else if (isUpdateShape)
        QMessageBox::critical(this, "Ошибка ", "Процесс обновления отсекателя уже запущен", QMessageBox::Ok);
    else {
        m_pScene->clear();
        vPolygonDots.clear();
        m_pPen->setColor(QColor(0, 255, 0));
        for (auto line: m_vLines)
            DrawLineDDA(line.front(), line.back());
        isUpdateShape = true;
    }
}

void CanvasPolygon::lockPolygon() {
    m_pPen->setColor(QColor(255, 0, 0));
    DrawLineDDA(vPolygonDots.back(), vPolygonDots.front());
    isUpdateShape = false;
    if (GetDirection() == 0) {
        QMessageBox::critical(this, "Ошибка ", "Отсекатель не выпуклый многоугольник!", QMessageBox::Ok);
        m_pScene->clear();
        m_pPen->setColor(QColor(0, 255, 0));
        for (auto line: m_vLines)
            DrawLineDDA(line.front(), line.back());
        vPolygonDots.clear();
    }
    else {
        direction = GetDirection();
        vNormals = GetNormals(direction);
        for (auto line: m_vLines)
        {
            auto cuttedLine = cutLine(line.front(), line.back());
            m_pPen->setColor(QColor(0, 0, 255));
            if (!cuttedLine.empty())
                DrawLineDDA(cuttedLine.front(), cuttedLine.back());
        }
    }
}

line_t CanvasPolygon::cutLine(dot_t A, dot_t B) {
    double tDown = 0, tUp = 1;
    double tTemp;

    Vector D(A, B);
    Vector W;

    double DScalar, WScalar;

    for (size_t i = 0; i < vPolygonDots.size(); i++)
    {
        W = Vector(vPolygonDots[i], A);
        DScalar = Vector::Scalar(D, vNormals[i]);
        WScalar = Vector::Scalar(W, vNormals[i]);

        if (static_cast<int>(DScalar) == 0)
        {
            if (WScalar < 0)
                return line_t();
        }
        else
        {
            tTemp = -WScalar / DScalar;
            if (DScalar > 0)
            {
                if (tTemp > 1)
                    return line_t();
                if (tTemp > tDown)
                    tDown = tTemp;
            }
            else
            {
                if (tTemp < 0)
                    return line_t();
                if (tTemp < tUp)
                    tUp = tTemp;
            }
        }

        if (tDown > tUp)
            return line_t();
    }
    dot_t newA(A.first + D.getX() * tDown, A.second + D.getY() * tDown);
    dot_t newB(A.first + D.getX() * tUp, A.second + D.getY() * tUp);

    line_t res;
    res.push_back(newA);
    res.push_back(newB);
    return res;
}

// 1 - vs chas
// 0 - nevip
// -1 - chas
int CanvasPolygon::GetDirection() {
    if (vPolygonDots.size() < 3)
        return 0;
    Vector A(vPolygonDots.back(), vPolygonDots.front());

    int sign = 0;

    for (size_t i = 0; i < vPolygonDots.size(); i++)
    {
        Vector B;
        if (i + 1 != vPolygonDots.size())
            B = Vector(vPolygonDots[i], vPolygonDots[i + 1]);
        else
            B = Vector(vPolygonDots[i], vPolygonDots[0]);
        int res = 0;
        if (Vector::Multiplication(A, B) > 0)
            res = 1;
        else if (Vector::Multiplication(A, B) < 0)
            res = -1;
        if (res != 0)
        {
            if (sign == 0)
                sign = res;
            else if (sign != res)
                return 0;
        }
        A = B;
    }
    return sign;
}

std::vector<Vector> CanvasPolygon::GetNormals(int dir) {
    vNormals.clear();

    Vector N;
    double tmp;
    for (int i = 0; i < vPolygonDots.size() - 1; i++)
    {
        N = Vector(vPolygonDots[i], vPolygonDots[i + 1]);
        tmp = N.getX();
        N.setX(-N.getY());
        N.setY(tmp);

        if (dir == -1)
            N.Negative();
        vNormals.push_back(N);
    }
    N = Vector(vPolygonDots.back(), vPolygonDots.front());
    tmp = N.getX();
    N.setX(-N.getY());
    N.setY(tmp);

    if (dir == -1)
        N.Negative();
    vNormals.push_back(N);
    return vNormals;
}
