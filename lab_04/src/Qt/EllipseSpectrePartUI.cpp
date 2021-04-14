//
// Created by denis on 13.04.2021.
//

#include <QtWidgets/QFormLayout>
#include "Qt/EllipseSpectrePartUI.h"
#include "Qt/EditLineUpdated.h"

EllipseSpectrePartUI::EllipseSpectrePartUI() {
    auto axisStepLine = new EditLineUpdated;
    auto ellipseNumbLine = new EditLineUpdated;

    auto axisStepForm = new QFormLayout;
    auto ellipseNumbForm = new QFormLayout;

    axisStepForm->addRow("axis step", axisStepLine);
    ellipseNumbForm->addRow("ellipse numb", ellipseNumbLine);

    addLayout(axisStepForm, 0, 0);
    addLayout(ellipseNumbForm, 1, 0);

    m_pAxisStep = axisStepLine;
    m_pEllipseNumb = ellipseNumbLine;
}

bool EllipseSpectrePartUI::GetAxisStep(double &res) {
    return m_pAxisStep->toDouble(res);
}

bool EllipseSpectrePartUI::GetEllipseNumb(double &res) {
    return m_pEllipseNumb->toDouble(res);
}
