//
// Created by denis on 14.03.2021.
//

#include <cmath>
#include "DrawLine.h"

void drawPixel(dot pixel, QGraphicsScene *scene, const QPen& pen)
{
    scene->addLine(pixel.first, pixel.second, pixel.first, pixel.second, pen);
}

void DrawLine::drawCircle(DrawType type, DrawColor color, dot center, double R, QGraphicsScene *scene) {

    auto pen = makePenWithColor(color);
    switch (type) {
        case DrawType::Qt:
            DrawQtCircle(center, R, scene, pen);
            break;
        case DrawType::Canonical:
            DrawCanonicalCircle(center, R, scene, pen);
            break;
        case DrawType::Parametric:
            DrawParametricCircle(center, R, scene, pen);
            break;
        case DrawType::Brezenhem:
            DrawBrezenhemCircle(center, R, scene, pen);
            break;
        case DrawType::CenterDot:
            DrawCenterDotCircle(center, R, scene, pen);
            break;
    }
}

void DrawLine::drawEllipse(DrawType type, DrawColor color, dot center, double xAxis, double yAxis, QGraphicsScene *scene) {
    auto pen = makePenWithColor(color);
    switch (type) {
        case DrawType::Qt:
            DrawQtEllipse(center, xAxis, yAxis, scene, pen);
            break;
        case DrawType::Canonical:
            DrawCanonicalEllipse(center, xAxis, yAxis, scene, pen);
            break;
        case DrawType::Parametric:
            DrawParametricEllipse(center, xAxis, yAxis, scene, pen);
            break;
        case DrawType::Brezenhem:
            DrawBrezenhemEllipse(center, xAxis, yAxis, scene, pen);
            break;
        case DrawType::CenterDot:
            DrawCenterDotEllipse(center, xAxis, yAxis, scene, pen);
            break;
    }
}



QPen DrawLine::makePenWithColor(DrawColor color) {
    QPen drawPen;
    drawPen.setColor(getColorByType(color));
    return drawPen;
}

QColor DrawLine::getColorByType(DrawColor color) {
    switch (color) {
        case DrawColor::White:
            return QColor(255, 255, 255);
        case DrawColor::Black:
            return QColor(0, 0, 0);
        case DrawColor::Red:
            return QColor(255, 0, 0);
        case DrawColor::Green:
            return QColor(0, 255, 0);
        case DrawColor::Blue:
            return QColor(0, 0, 255);
        case DrawColor::Yellow:
            return QColor(255, 255, 0);
        default:
            return QColor(0, 0, 0);
    }
}

void DrawLine::DrawCanonicalEllipse(dot center, double xR, double yR, QGraphicsScene *scene, const QPen &pen) {

    int a2 = xR * xR;
    int b2 = yR * yR;

    // Производная при y'= -1 , является границей для оптимального рисования
    // y'= -b^2/a^2 * x/y
    // b^2 * x = a^2 * y

    int i = 0, j = yR;
    // dx = 1
    while (b2 * i < a2 * j)
    {
        drawPixel(dot(center.first + i, center.second + j), scene, pen);
        drawPixel(dot(center.first + i, center.second - j), scene, pen);
        drawPixel(dot(center.first - i, center.second + j), scene, pen);
        drawPixel(dot(center.first - i, center.second - j), scene, pen);

        i++;
        j = round(yR / xR * sqrt(a2 - i * i));
    }

    // dy = -1
    while (j >= 0)
    {
        drawPixel(dot(center.first + i, center.second + j), scene, pen);
        drawPixel(dot(center.first + i, center.second - j), scene, pen);
        drawPixel(dot(center.first - i, center.second + j), scene, pen);
        drawPixel(dot(center.first - i, center.second - j), scene, pen);

        j--;
        i = round(xR / yR * sqrt(b2 - j * j));
    }
}

void DrawLine::DrawParametricEllipse(dot center, double xR, double yR, QGraphicsScene *scene, const QPen &pen) {
    double step = xR > yR ? yR / (xR * xR) : xR / (yR * yR);
    int i, j;
    for (double t = 0; t < M_PI_2 + step / 2; t += step)
    {
        i = round(xR * cos(t));
        j = round(yR * sin(t));

        drawPixel(dot(center.first + i, center.second + j), scene, pen);
        drawPixel(dot(center.first + i, center.second - j), scene, pen);
        drawPixel(dot(center.first - i, center.second + j), scene, pen);
        drawPixel(dot(center.first - i, center.second - j), scene, pen);
    }
}

void DrawLine::DrawQtEllipse(dot center, double xR, double yR, QGraphicsScene *scene, const QPen &pen) {
    scene->addEllipse(center.first - xR, center.second - yR, 2 * xR, 2 * yR, pen);
}

inline void DiagonalStepEllipse(int& x, int& y, int a2, int b2, int& d)
{
    x++;
    y--;
    d += b2 * (2 * x + 1) + a2 * (1 - 2 * y);
}

inline void HorizontalStepEllipse(int& x, int& y, int a2, int b2, int& d)
{
    x++;
    d += b2 * (2 * x + 1);
}

inline void VerticalStepEllipse(int& x, int& y, int a2, int b2, int& d)
{
    y--;
    d += a2 * (1 - 2 * y);
}


void DrawLine::DrawBrezenhemEllipse(dot center, double xR, double yR, QGraphicsScene *scene, const QPen &pen) {
    int a2 = xR * xR;
    int b2 = yR * yR;
    int d = a2 + b2 - 2 * a2 * yR;
    int i = 0, j = yR;
    while (j > 0)
    {
        drawPixel(dot(center.first + i, center.second + j), scene, pen);
        drawPixel(dot(center.first + i, center.second - j), scene, pen);
        drawPixel(dot(center.first - i, center.second + j), scene, pen);
        drawPixel(dot(center.first - i, center.second - j), scene, pen);

        if (d == 0) // диагональная точка лежит на эллипсе
            DiagonalStepEllipse(i, j, a2, b2, d);
        else if (d < 0) // диагональная точка внутри эллипса
        {
            //  раст. до гор пикселя      раст. до диаг. пикселя
            // |b^2(xi+1)^2 + a^2yi^2 - a^2b^2| - |b^2(xi+1)^2 + a^2(yi-1)^2 - a^2b^2|
            int delta1 = 2 * (d + a2 * j) - a2;
            if (delta1 > 0)
                DiagonalStepEllipse(i, j, a2, b2, d);
            else
                HorizontalStepEllipse(i, j, a2, b2, d);
        }

        else // диагональная точка вне эллипса
        {
            //  раст. до диаг. пикселя        раст. до верт пикселя
            // |b^2(xi+1)^2 + a^2(yi-1)^2 - a^2b^2| - |b^2xi^2 + a^2(yi-1)^2 - a^2b^2|
            int delta2 = 2 * (d - b2 * i) - b2;
            if (delta2 < 0)
                DiagonalStepEllipse(i, j, a2, b2, d);
            else
                VerticalStepEllipse(i, j, a2, b2, d);
        }
    }
    drawPixel(dot(center.first + i, center.second + j), scene, pen);
    drawPixel(dot(center.first + i, center.second - j), scene, pen);
    drawPixel(dot(center.first - i, center.second + j), scene, pen);
    drawPixel(dot(center.first - i, center.second - j), scene, pen);
}

void DrawLine::DrawCenterDotEllipse(dot center, double xR, double yR, QGraphicsScene *scene, const QPen &pen) {
    int a2 = xR * xR;
    int b2 = yR * yR;

    int ad = 2 * a2;
    int bd = 2 * b2;

    int i = 0, j = yR;

    // tпр = b^2*x^2 + a^2*y^2 - a^2 * b^2;
    // начальное значение средней точки M(1, b-1/2.)
    float t = a2 / 4. - a2 * yR + b2;

    // Производная при y'= -1 , является границей для оптимального рисования
    // y'= -b^2/a^2 * x/y
    while (b2 * i < a2 * j)
    {
        drawPixel(dot(center.first + i, center.second + j), scene, pen);
        drawPixel(dot(center.first + i, center.second - j), scene, pen);
        drawPixel(dot(center.first - i, center.second + j), scene, pen);
        drawPixel(dot(center.first - i, center.second - j), scene, pen);


        // M вне эллипса, ближе диагональный пиксель
        if (t >= 0)
        {
            j--;
            t -= ad * j;
        }

        i++;
        t += bd * i + b2;
    }

    t += 3 / 4. * (a2 - b2) - (b2 * i + a2 * j);

    while (j > 0)
    {
        drawPixel(dot(center.first + i, center.second + j), scene, pen);
        drawPixel(dot(center.first + i, center.second - j), scene, pen);
        drawPixel(dot(center.first - i, center.second + j), scene, pen);
        drawPixel(dot(center.first - i, center.second - j), scene, pen);

        // M внутри эллипса, ближе диагональный пиксель
        if (t <= 0)
        {
            i++;
            t += bd * i;
        }
        j--;
        t += -ad * j + a2;
    }

    drawPixel(dot(center.first + i, center.second + j), scene, pen);
    drawPixel(dot(center.first + i, center.second - j), scene, pen);
    drawPixel(dot(center.first - i, center.second + j), scene, pen);
    drawPixel(dot(center.first - i, center.second - j), scene, pen);
}

void DrawLine::DrawQtCircle(dot center, double R, QGraphicsScene *scene, const QPen &pen) {
    scene->addEllipse(center.first - R, center.second - R, 2 * R, 2 * R, pen);
}

void DrawLine::DrawCanonicalCircle(dot center, double R, QGraphicsScene *scene, const QPen &pen) {
    double r2 = R * R;
    double i = 0, j = R;
    while (i < j)
    {
        drawPixel(dot(center.first + i, center.second + j), scene, pen);
        drawPixel(dot(center.first + i, center.second - j), scene, pen);
        drawPixel(dot(center.first - i, center.second + j), scene, pen);
        drawPixel(dot(center.first - i, center.second - j), scene, pen);

        drawPixel(dot(center.first + j, center.second + i), scene, pen);
        drawPixel(dot(center.first + j, center.second - i), scene, pen);
        drawPixel(dot(center.first - j, center.second + i), scene, pen);
        drawPixel(dot(center.first - j, center.second - i), scene, pen);

        i++;
        j = round(sqrt(r2 - i * i));
    }
    drawPixel(dot(center.first + i, center.second + j), scene, pen);
    drawPixel(dot(center.first + i, center.second - j), scene, pen);
    drawPixel(dot(center.first - i, center.second + j), scene, pen);
    drawPixel(dot(center.first - i, center.second - j), scene, pen);
}

void DrawLine::DrawParametricCircle(dot center, double R, QGraphicsScene *scene, const QPen &pen) {
    double step = 1 / R;
    int i, j;
    for (double t = 0; t < M_PI_4; t += step)
    {
        i = static_cast<int>(round(R * cos(t)));
        j = static_cast<int>(round(R * sin(t)));

        drawPixel(dot(center.first + i, center.second + j), scene, pen);
        drawPixel(dot(center.first + i, center.second - j), scene, pen);
        drawPixel(dot(center.first - i, center.second + j), scene, pen);
        drawPixel(dot(center.first - i, center.second - j), scene, pen);

        drawPixel(dot(center.first + j, center.second + i), scene, pen);
        drawPixel(dot(center.first + j, center.second - i), scene, pen);
        drawPixel(dot(center.first - j, center.second + i), scene, pen);
        drawPixel(dot(center.first - j, center.second - i), scene, pen);
    }

    i = round(R * M_SQRT1_2);
    j = i;
    drawPixel(dot(center.first + i, center.second + j), scene, pen);
    drawPixel(dot(center.first + i, center.second - j), scene, pen);
    drawPixel(dot(center.first - i, center.second + j), scene, pen);
    drawPixel(dot(center.first - i, center.second - j), scene, pen);
}

inline void DiagonalStepCicrle(int& x, int& y, int& d)
{
    x++;
    y--;
    d += 2 * (x - y + 1);
}

inline void HorizontalStepCicrle(int& x, int& y, int& d)
{
    x++;
    d += 2 * x + 1;
}

inline void VerticalStepCicrle(int& x, int& y, int& d)
{
    y--;
    d += -2 * y + 1;
}

void DrawLine::DrawBrezenhemCircle(dot center, double R, QGraphicsScene *scene, const QPen &pen) {
    int r2 = static_cast<int>(R * R);
    int d = 2 * (1 - R); // первоначальная ошибка

    int i = 0, j = R;
    while (i < j)
    {
        drawPixel(dot(center.first + i, center.second + j), scene, pen);
        drawPixel(dot(center.first + i, center.second - j), scene, pen);
        drawPixel(dot(center.first - i, center.second + j), scene, pen);
        drawPixel(dot(center.first - i, center.second - j), scene, pen);

        drawPixel(dot(center.first + j, center.second + i), scene, pen);
        drawPixel(dot(center.first + j, center.second - i), scene, pen);
        drawPixel(dot(center.first - j, center.second + i), scene, pen);
        drawPixel(dot(center.first - j, center.second - i), scene, pen);

        if (d == 0) // диагональная точка лежит на окружности
            DiagonalStepCicrle(i, j, d);
        else if (d < 0) // диагональная точка внутри окружности
        {
            //  раст. до гор пикселя      раст. до диаг. пикселя
            // |(xi+1)^2 + yi^2 - r^2| - |(xi+1)^2 + (yi-1)^2 - r^2|
            int delta1 = 2 * (d + j) - 1;
            if (delta1 > 0)
                DiagonalStepCicrle(i, j, d);
            else
                HorizontalStepCicrle(i, j, d);
        }

        else // диагональная точка вне окружности
        {
            //  раст. до диаг. пикселя        раст. до верт пикселя
            // |(xi+1)^2 + (yi-1)^2 - r^2| - |xi^2 + (yi-1)^2 - r^2|
            int delta2 = 2 * (d - i) - 1;
            if (delta2 < 0)
                DiagonalStepCicrle(i, j, d);
            else
                VerticalStepCicrle(i, j, d);
        }
    }
    drawPixel(dot(center.first + i, center.second + j), scene, pen);
    drawPixel(dot(center.first + i, center.second - j), scene, pen);
    drawPixel(dot(center.first - i, center.second + j), scene, pen);
    drawPixel(dot(center.first - i, center.second - j), scene, pen);
}

void DrawLine::DrawCenterDotCircle(dot center, double R, QGraphicsScene *scene, const QPen &pen) {
    int i = 0, j = R;
    // t = x^2 + y^2 - r^2
    // t(1, r-1/2.)
    // t = 5 / 4 - r
    // 0,25 можно отбросить
    // начинаем с целого числа и каждый раз прибавляем целое число
    // невозможна ситуация целое число + 0,25 получить ноль
    int t = 1 - R;

    // t += 2 * i + 3; при горизонтальном шаге
    // t += 2 * (i - j) + 5 при диагональном шаге
    int incrA = 3; // i = 0
    int incrB = 5 - 2 * R; // i = 0, j = r
    while(i < j)
    {
        drawPixel(dot(center.first + i, center.second + j), scene, pen);
        drawPixel(dot(center.first + i, center.second - j), scene, pen);
        drawPixel(dot(center.first - i, center.second + j), scene, pen);
        drawPixel(dot(center.first - i, center.second - j), scene, pen);

        drawPixel(dot(center.first + j, center.second + i), scene, pen);
        drawPixel(dot(center.first + j, center.second - i), scene, pen);
        drawPixel(dot(center.first - j, center.second + i), scene, pen);
        drawPixel(dot(center.first - j, center.second - i), scene, pen);

        // если диагональный пиксель ближе
        if (t >= 0)
        {
            // скорректировать пробную функцию
            t += incrB;
            incrB += 4;
            j--;
        }
        else
        {
            t += incrA;
            incrB += 2;
        }
        incrA += 2;
        i++;
    }
    drawPixel(dot(center.first + i, center.second + j), scene, pen);
    drawPixel(dot(center.first + i, center.second - j), scene, pen);
    drawPixel(dot(center.first - i, center.second + j), scene, pen);
    drawPixel(dot(center.first - i, center.second - j), scene, pen);
}













