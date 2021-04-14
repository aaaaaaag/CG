//
// Created by denis on 08.04.2021.
//

#include <QtWidgets/QFormLayout>
#include "Qt/CirclePartUI.h"


CirclePartUI::CirclePartUI() {
    auto radiusLine = new EditLineUpdated;
    auto centerXLine = new EditLineUpdated;
    auto centerYLine = new EditLineUpdated;

    auto radiusForm = new QFormLayout;
    auto centerXForm = new QFormLayout;
    auto centerYForm = new QFormLayout;

    radiusForm->addRow("Radius", radiusLine);
    centerXForm->addRow("Center X", centerXLine);
    centerYForm->addRow("Center Y", centerYLine);

    addLayout(centerXForm, 0, 0);
    addLayout(centerYForm, 0, 1);
    addLayout(radiusForm, 1, 0);

    m_pRadius = radiusLine;
    m_pXCenter = centerXLine;
    m_pYCenter = centerYLine;
}

bool CirclePartUI::GetCenter(dot &res) {
    if (!m_pXCenter->toDouble(res.first) || !m_pYCenter->toDouble(res.second))
        return false;
    return true;
}

bool CirclePartUI::GetRadius(double &res) {
    if (!m_pRadius->toDouble(res))
        return false;
    return true;
}