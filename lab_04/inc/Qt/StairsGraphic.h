//
// Created by denis on 30.03.2021.
//

#ifndef LAB_03_STAIRSGRAPHIC_H
#define LAB_03_STAIRSGRAPHIC_H

#include "QtCharts/QtCharts"

#include "DrawLine.h"

using namespace QtCharts;

class StairsGraphic: public QChart {
public:

    StairsGraphic();

    void ConnectButton(QPushButton* button) const;

private slots:

    void CreateGraphic();

private:

    static QLineSeries* CreateChangeLine(DrawType type);
};


#endif //LAB_03_STAIRSGRAPHIC_H
