//
// Created by denis on 14.03.2021.
//

#include "DrawLine.h"
int sign(double numb)
{
    if (numb < 0)
        return -1;
    else if (numb > 0)
        return 1;
    return 0;
}


void drawPixel(dot pixel, QGraphicsScene *scene, const QPen& pen)
{
    scene->addLine(pixel.first, pixel.second, pixel.first, pixel.second, pen);
}

void drawPixel(dot pixel, QGraphicsScene *scene, QPen pen, double alpha)
{
    auto color = pen.color();
    color.setAlpha(static_cast<int>(abs(alpha) * 255 * 2));
    pen.setColor(color);
    drawPixel(pixel, scene, pen);
}

int DrawLine::drawLine(DrawType type, DrawColor color, dot from, dot to, QGraphicsScene *scene) {
    int steps = 0;
    QPen drawPen = makePenWithColor(color);
    switch (type) {
        case DrawType::Qt:
            drawLineQt(from, to, scene, drawPen);
            break;
        case DrawType::DDA:
            steps = drawLineDDA(from, to, scene, drawPen);
            break;
        case DrawType::BrezenhemInt:
            steps = drawLineBrezenhemInt(from, to, scene, drawPen);
            break;
        case DrawType::BrezenhemFloat:
            steps = drawLineBrezenhemFloat(from, to, scene, drawPen);
            break;
        case DrawType::BrezenhemStairs:
            drawLineBrezenhemStairs(from, to, scene, drawPen);
            break;
        case DrawType::Woo:
            drawLineWoo(from, to, scene, drawPen);
            break;
    }
    return steps;
}

void DrawLine::drawLineQt(dot from, dot to, QGraphicsScene *scene, const QPen& pen) {
    scene->addLine(QLine(from.first, from.second, to.first, to.second), pen);
}

int DrawLine::drawLineDDA(dot from, dot to, QGraphicsScene *scene, const QPen& pen) {

    double x1 = from.first, x2 = to.first, y1 = from.second, y2 = to.second, length;

    auto dx = x2 - x1;
    auto dy = y2 - y1;

    if (abs(dx) - abs(dy) >= 0) length = abs(dx);
    else length = abs(dy);

    dx /= length; dy /= length;
    auto x = x1, y = y1;

    int prevX, prevY;
    int stairsNumb = 0;
    for (int i = 0; i < length + 1; i++)
    {
        prevX = x;
        prevY = y;
        drawPixel(dot(x, y), scene, pen);
        x += dx; y += dy;
        if (prevX == static_cast<int>(x) - 1 && prevY == static_cast<int>(y) - 1)
            stairsNumb++;
    }
    return stairsNumb;
}

int DrawLine::drawLineBrezenhemFloat(dot from, dot to, QGraphicsScene *scene, const QPen &pen) {
    double x1 = from.first, x2 = to.first, y1 = from.second, y2 = to.second;
    auto x = x1, y = y1;

    auto dx = x2 - x1, dy = y2 - y1;

    auto s1 = sign(dx), s2 = sign(dy);
    dx = abs(dx);
    dy = abs(dy);

    int change = 0;
    if (dy > dx)
    {
        auto tmp = dx;
        dx = dy;
        dy = tmp;
        change = 1;
    }

    auto m = dy / dx;
    auto e = m - 0.5;
    int stairsNumb = 0;
    int prevX, prevY;

    for (int i = 1; i < dx + 1; i++)
    {
        prevX = x;
        prevY = y;
        drawPixel(dot(x, y), scene, pen);
        if (e >= 0)
        {
            if (change == 1) x += s1;
            else y += s2;
            e--;
        }
        if (change == 1)
            y += s2;
        else
            x += s1;
        if (prevX == static_cast<int>(x) - 1 && prevY == static_cast<int>(y) - 1)
            stairsNumb++;
        e += m;
    }
    return stairsNumb;
}

int DrawLine::drawLineBrezenhemInt(dot from, dot to, QGraphicsScene *scene, const QPen &pen) {

    double x1 = from.first, x2 = to.first, y1 = from.second, y2 = to.second;
    auto x = x1, y = y1;

    auto dx = x2 - x1, dy = y2 - y1;

    auto s1 = sign(dx), s2 = sign(dy);
    dx = abs(dx);
    dy = abs(dy);

    int change = 0;
    if (dy > dx)
    {
        auto tmp = dx;
        dx = dy;
        dy = tmp;
        change = 1;
    }

    auto e = 2 * dy - dx;
    int stairsNumb = 0;
    int prevX, prevY;
    for (int i = 1; i < dx + 1; i++)
    {
        prevX = x;
        prevY = y;
        drawPixel(dot(x, y), scene, pen);
        if (e >= 0)
        {
            if (change == 1) x += s1;
            else y += s2;
            e -= (2 * dx);
        }
        if (change == 1) y += s2;
        else x += s1;
        if (prevX == static_cast<int>(x) - 1 && prevY == static_cast<int>(y) - 1)
            stairsNumb++;
        e += (2 * dy);
    }
    return stairsNumb;
}

void DrawLine::drawLineBrezenhemStairs(dot from, dot to, QGraphicsScene *scene, QPen pen) {
    double x1 = from.first, x2 = to.first, y1 = from.second, y2 = to.second;

    auto x = x1, y = y1;
    auto dx = x2 - x1, dy = y2 - y1;
    auto sx = sign(dx), sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    int swap = 0;
    if (dy > dx) {
        swap = 1;
        std::swap(dx, dy);
    }

    double m = dy / dx;
    double e = 0.5;

    for (int i = 1; i < dx + 1; i++)
    {
//        auto color = pen.color();
//        color.setAlpha(static_cast<int>(abs(1 - e) * 255));
//        pen.setColor(color);
        drawPixel(dot(x, y), scene, pen, 1 - e);
        if (e >= 1)
        {
            if (swap == 0) y += sy;
            else x += sx;
            e -= 1;
        }

        if (swap == 0) x += sx;
        else y += sy;
        e += m;
    }
}


double getFPart(double numb)
{
    return numb - static_cast<int>(numb);
}

void DrawLine::drawLineWoo(dot from, dot to, QGraphicsScene *scene, QPen pen) {

    double x1 = from.first, y1 = from.second, x2 = to.first, y2 = to.second;
//
//    if (x2 < x1)
//    {
//        std::swap(x1, x2);
//        std::swap(y1, y2);
//    }
//
//    auto dx = x2 - x1, dy = y2 - y1;
//    auto gradient = dy / dx;
//
//    int xEnd = static_cast<int>(x1);
//    int yEnd = static_cast<int>(y1 + gradient * (xEnd - x1));
//    auto xgap = 1 - getFPart(x1 + 0.5);
//    int xPxl1 = xEnd;
//    int yPxl1 = static_cast<int>(yEnd);
//    drawPixel(dot(xPxl1, yPxl1), scene, pen, (1 - getFPart(yEnd) * xgap));
//    drawPixel(dot(xPxl1, yPxl1 + 1), scene, pen, getFPart(yEnd) * xgap);
//    auto intery = yEnd + gradient;
//
//    xEnd = static_cast<int>(x2 + 0.5);
//    yEnd = y2 + gradient * (xEnd - x2);
//    xgap = getFPart(x2 + 0.5);
//    int xPxl2 = xEnd;
//    int yPxl2 = static_cast<int>(yEnd);
//    drawPixel(dot(xPxl2, yPxl2), scene, pen, (1 - getFPart(yEnd) * xgap));
//    drawPixel(dot(xPxl2, yPxl2 + 1), scene, pen, getFPart(yEnd) * xgap);
//
//    for (int x = xPxl1 = 1; x < xPxl2; x++)
//    {
//        drawPixel(dot(x, static_cast<int>(intery)), scene, pen, 1 - getFPart(intery));
//        drawPixel(dot(x, static_cast<int>(intery) + 1), scene, pen, getFPart(intery));
//        intery += gradient;
//    }











    //+++++++++++++++++++++











    auto dx = x2 - x1;
    auto dy = y2 - y1;
    auto x = x1, y = y1;
    auto sx = sign(dx), sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    int change = 0;
    if (dy > dx)
    {
        change = 1;
        std::swap(dx, dy);
    }

    auto m = dy / dx;
    auto e = 0.5;
    auto w = 1;

    for (int i = 0; i < dx + 1; i++)
    {
        drawPixel(dot(x, y), scene, pen, e);
        if (change == 0) drawPixel(dot(x, y + sy), scene, pen, e - 1);
        else drawPixel(dot(x + sx, y), scene, pen, e - 1);

        if (e >= w - m)
        {
            if (change == 0) y += sy;
            else x += sx;
            e -= 1;
        }
        if (change == 1) y += sy;
        else x += sx;

        e += m;
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










