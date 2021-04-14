//
// Created by denis on 20.03.2021.
//

#include "Qt/SpectreUI.h"
#include "QFormLayout"
#include "Qt/EditLineUpdated.h"

SpectreUI::SpectreUI() {
    auto degreesLine = new EditLineUpdated;
    auto lineLength = new EditLineUpdated;

    auto degreesForm = new QFormLayout;
    auto lineLengthForm = new QFormLayout;

    degreesForm->addRow("Degrees", degreesLine);
    lineLengthForm->addRow("Cut length", lineLength);

    addLayout(degreesForm, 0, 0);
    addLayout(lineLengthForm, 1, 0);

    m_pDegreesLine = degreesLine;
    m_pCutLength = lineLength;
}

bool SpectreUI::GetDegrees(double& res) {
    return m_pDegreesLine->toDouble(res);
}

bool SpectreUI::GetLineLength(double& res) {
    return m_pCutLength->toDouble(res);
}


