//
// Created by denis on 13.04.2021.
//

#include <QtWidgets/QFormLayout>
#include "Qt/CircleSpectrePartUI.h"
#include "Qt/EditLineUpdated.h"

CircleSpectrePartUI::CircleSpectrePartUI() {
    auto startRadiusLine = new EditLineUpdated;
    auto endRadiusLine = new EditLineUpdated;
    auto radiusStepLine = new EditLineUpdated;
    auto circleNumbLine = new EditLineUpdated;

    auto startRadiusForm = new QFormLayout;
    auto endRadiusForm = new QFormLayout;
    auto radiusStepForm = new QFormLayout;
    auto circleNumbForm = new QFormLayout;

    startRadiusForm->addRow("Start radius", startRadiusLine);
    endRadiusForm->addRow("End radius", endRadiusLine);
    radiusStepForm->addRow("Radius step", radiusStepLine);
    circleNumbForm->addRow("Circle numb", circleNumbLine);

    addLayout(startRadiusForm, 0, 0);
    addLayout(endRadiusForm, 0, 1);
    addLayout(radiusStepForm, 1, 0);
    addLayout(circleNumbForm, 1, 1);

    m_pStartRadius = startRadiusLine;
    m_pEndRadius = endRadiusLine;
    m_pRadiusStep = radiusStepLine;
    m_pCircleNumb = circleNumbLine;
}

bool CircleSpectrePartUI::GetStartRadius(double &res) {
    return m_pStartRadius->toDouble(res);
}

bool CircleSpectrePartUI::GetEndRadius(double &res) {
    return m_pEndRadius->toDouble(res);
}

bool CircleSpectrePartUI::GetRadiusStep(double &step) {
    return m_pRadiusStep->toDouble(step);
}

bool CircleSpectrePartUI::GetCircleNumb(double &res) {
    return m_pCircleNumb->toDouble(res);
}
