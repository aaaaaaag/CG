//
// Created by denis on 14.03.2021.
//

#include "Qt/EntryLineCoords.h"
#include "QFormLayout"
#include "Qt/EditLineUpdated.h"

EntryLineCoords::EntryLineCoords() {

    auto xStartLine = new EditLineUpdated;
    auto yStartLine = new EditLineUpdated;
    auto xEndLine = new EditLineUpdated;
    auto yEndLine = new EditLineUpdated;

    auto xStartForm = new QFormLayout;
    auto yStartForm = new QFormLayout;
    auto xEndForm = new QFormLayout;
    auto yEndForm = new QFormLayout;

    xStartForm->addRow("Start x", xStartLine);
    yStartForm->addRow("Start y", yStartLine);
    xEndForm->addRow("End x", xEndLine);
    yEndForm->addRow("End y", yEndLine);

    addLayout(xStartForm, 1, 0);
    addLayout(yStartForm, 2, 0);
    addLayout(xEndForm, 3, 0);
    addLayout(yEndForm, 4, 0);

    mXStartLine = xStartLine;
    mYStartLine = yStartLine;
    mXEndLine = xEndLine;
    mYEndLine = yEndLine;
}

bool EntryLineCoords::GetStartCoord(dot &res) {
    double xCoord, yCoord;
    if (!mXStartLine->toDouble(xCoord) || !mYStartLine->toDouble(yCoord))
        return false;
    res = dot(xCoord, yCoord);
    return true;
}

bool EntryLineCoords::GetEndCoord(dot &res) {
    double xCoord, yCoord;
    if (!mXEndLine->toDouble(xCoord) || !mYEndLine->toDouble(yCoord))
        return false;
    res = dot(xCoord, yCoord);
    return true;
}
