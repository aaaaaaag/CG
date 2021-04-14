//
// Created by denis on 14.03.2021.
//

#include "Qt/EditLineUpdated.h"
#include "CheckString.h"

bool EditLineUpdated::toDouble(double& res) {
    res = 0;
    auto lineData = this->text().toStdString();
    if (!CheckString::isDouble(lineData))
        return false;

    res = std::stof(lineData);
    return true;
}

