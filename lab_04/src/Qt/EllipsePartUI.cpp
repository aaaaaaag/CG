//
// Created by denis on 13.04.2021.
//

#include "Qt/EllipsePartUI.h"
#include "QFormLayout"

bool EllipsePartUI::GetCenter(dot &res) {
    if (!xCenter->toDouble(res.first) || !yCenter->toDouble(res.second))
        return false;
    return true;
}

bool EllipsePartUI::GetXAxisLen(double &res) {
    if (!xAxis->toDouble(res))
        return false;
    return true;
}

bool EllipsePartUI::GetYAxisLen(double &res) {
    if (!yAxis->toDouble(res))
        return false;
    return true;
}

EllipsePartUI::EllipsePartUI() {

    auto centerXLine = new EditLineUpdated;
    auto centerYLine = new EditLineUpdated;
    auto xAxisLine = new EditLineUpdated;
    auto yAxisLine = new EditLineUpdated;

    auto centerXForm = new QFormLayout;
    auto centerYForm = new QFormLayout;
    auto xAxisForm = new QFormLayout;
    auto yAxisForm = new QFormLayout;

    centerXForm->addRow("Center X", centerXLine);
    centerYForm->addRow("Center Y", centerYLine);
    xAxisForm->addRow("X axis length", xAxisLine);
    yAxisForm->addRow("Y axis length", yAxisLine);


    addLayout(centerXForm, 0, 0);
    addLayout(centerYForm, 0, 1);
    addLayout(xAxisForm, 1, 0);
    addLayout(yAxisForm, 1, 1);


    xCenter = centerXLine;
    yCenter = centerYLine;
    xAxis = xAxisLine;
    yAxis = yAxisLine;
}
