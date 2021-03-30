//
// Created by denis on 14.03.2021.
//

#ifndef LAB_03_DRAWLINE_H
#define LAB_03_DRAWLINE_H

#include <utility>
#include "QGraphicsView"
#include "QPen"

enum class DrawType
{
    Qt = 1,
    DDA,
    BrezenhemFloat,
    BrezenhemInt,
    BrezenhemStairs,
    Woo
};

enum class DrawColor
{
    White = 1,
    Black,
    Red,
    Green,
    Blue,
    Yellow
};

typedef std::pair<double, double> dot;
class DrawLine {
public:

    static int drawLine(DrawType type, DrawColor color, dot from, dot to, QGraphicsScene *scene);

    static QColor getColorByType(DrawColor color);

private:

    static QPen makePenWithColor(DrawColor color);

    static void drawLineQt(dot from, dot to, QGraphicsScene *scene, const QPen& pen);

    static int drawLineDDA(dot from, dot to, QGraphicsScene *scene, const QPen& pen);

    static int drawLineBrezenhemInt(dot from, dot to, QGraphicsScene *scene, const QPen& pen);

    static int drawLineBrezenhemFloat(dot from, dot to, QGraphicsScene *scene, const QPen& pen);

    static void drawLineBrezenhemStairs(dot from, dot to, QGraphicsScene *scene, QPen pen);

    static void drawLineWoo(dot from, dot to, QGraphicsScene *scene, QPen pen);

};

#endif //LAB_03_DRAWLINE_H
