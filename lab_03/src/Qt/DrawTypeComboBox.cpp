//
// Created by denis on 14.03.2021.
//

#include "Qt/DrawTypeComboBox.h"

DrawTypeComboBox::DrawTypeComboBox() {
    addItem("Qt");
    addItem("ЦДА");
    addItem("Брезенхем вещ.");
    addItem("Брезенхем цел.");
    addItem("Брезенхем сглаживание");
    addItem("Ву");
}

DrawType DrawTypeComboBox::GetSelectedMode() {
    auto selectedName = this->currentText().toStdString();
    if (selectedName == "Qt")
        return DrawType::Qt;
    else if (selectedName == "ЦДА")
        return DrawType::DDA;
    else if (selectedName == "Брезенхем цел.")
        return DrawType::BrezenhemInt;
    else if (selectedName == "Брезенхем вещ.")
        return DrawType::BrezenhemFloat;
    else if (selectedName == "Брезенхем сглаживание")
        return DrawType::BrezenhemStairs;
    else if (selectedName == "Ву")
        return DrawType::Woo;
    return DrawType::Qt;
}
