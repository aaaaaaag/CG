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
    Canonical,
    Parametric,
    Brezenhem,
    CenterDot
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

    static void drawCircle(DrawType type, DrawColor color, dot center, double R, QGraphicsScene *scene);

    static void drawEllipse(DrawType type, DrawColor color, dot center, double xAxis, double yAxis, QGraphicsScene *scene);

    static QColor getColorByType(DrawColor color);

private:

    static QPen makePenWithColor(DrawColor color);

    static void DrawCanonicalCircle(dot center, double R, QGraphicsScene *scene, const QPen& pen);

    static void DrawParametricCircle(dot center, double R, QGraphicsScene *scene, const QPen& pen);

    static void DrawQtCircle(dot center, double R, QGraphicsScene *scene, const QPen& pen);

    static void DrawBrezenhemCircle(dot center, double R, QGraphicsScene *scene, const QPen& pen);

    static void DrawCenterDotCircle(dot center, double R, QGraphicsScene *scene, const QPen& pen);

    static void DrawCanonicalEllipse(dot center, double xR, double yR, QGraphicsScene *scene, const QPen& pen);

    static void DrawParametricEllipse(dot center, double xR, double yR, QGraphicsScene *scene, const QPen& pen);

    static void DrawQtEllipse(dot center, double xR, double yR, QGraphicsScene *scene, const QPen& pen);

    static void DrawBrezenhemEllipse(dot center, double xR, double yR, QGraphicsScene *scene, const QPen& pen);

    static void DrawCenterDotEllipse(dot center, double xR, double yR, QGraphicsScene *scene, const QPen& pen);
};

#endif //LAB_03_DRAWLINE_H
