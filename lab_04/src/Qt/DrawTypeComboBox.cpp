//
// Created by denis on 14.03.2021.
//

#include "Qt/DrawTypeComboBox.h"

DrawTypeComboBox::DrawTypeComboBox() {
    addItem("Qt");
    addItem("Брезенхем");
    addItem("Каноничное уравнение");
    addItem("Параметрическое уравнение");
    addItem("Метод центральной точки");
}

DrawType DrawTypeComboBox::GetSelectedMode() {
    auto selectedName = this->currentText().toStdString();
    if (selectedName == "Qt")
        return DrawType::Qt;
    else if (selectedName == "Брезенхем")
        return DrawType::Brezenhem;
    else if (selectedName == "Каноничное уравнение")
        return DrawType::Canonical;
    else if (selectedName == "Параметрическое уравнение")
        return DrawType::Parametric;
    else if (selectedName == "Метод центральной точки")
        return DrawType::CenterDot;
    return DrawType::Qt;
}
